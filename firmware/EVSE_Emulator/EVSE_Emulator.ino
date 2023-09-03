#include "config.h"

volatile long pwm_adc_value = 0;
volatile int average_counter = 0;
volatile bool pilot_adc_flag = LOW;

int fsm_state = STATE_IDLE;

void setup() {

  // Debug Pin
  pinMode(7, OUTPUT);

  Serial.begin(115200);
  init_leds();

  Serial.println("EVSE Emulator 1.0");
}

void loop() {

  if (pilot_adc_flag) {

    float pilot_volt = mapfloat(pwm_adc_value / average_counter, 160, 840, -12.0, 12.0);
    Serial.println("Pilot Voltage:" + String(pilot_volt) + " [raw: " + String(pwm_adc_value / average_counter) + "]");
    fsm_state = volt2state(pilot_volt);

    pwm_adc_value = 0;
    average_counter = 0;
    pilot_adc_flag = LOW;  // Reset flag
  }

  set_statusleds(fsm_state);

  switch (fsm_state) {
    case STATE_IDLE:
      Serial.println("FSM: IDLE");
      set_pwm(PWM_ALWAYS_ON);
      break;
    case STATE_CONNECTED:
      Serial.println("FSM: CONNECTED");
      delay(500);
      set_pwm(PWM_30A);
      break;
    case STATE_CHARGING:
      Serial.println("FSM: CHARGING");
      set_pwm(PWM_30A);
      break;
    case STATE_COOLING:
      Serial.println("FSM: COOLING");
      set_pwm(PWM_30A);
      break;
    case STATE_CONERROR:
      Serial.println("FSM: CONNECTION ERROR");
      set_pwm(PWM_ALWAYS_ON);
      break;
    case STATE_ERROR:
      Serial.println("FSM: ERROR");
      set_pwm(PWM_ALWAYS_ON);
      //fsm_state = STATE_IDLE;
      break;
    default:
      Serial.println("FSM: We should not be here...");
      set_pwm(PWM_ALWAYS_ON);
      //fsm_state = STATE_ERROR;
      break;
  }

  delay(500);
}


// Timer Compare A Interrupt vector, called with rising edge of PWM
// Used for ADC measurement during high cycle
ISR(TIMER2_COMPA_vect) {  // called by timer2

  delayMicroseconds(50);  // wait for value to stabilize

  // Check if we need to acquire more samples (Flag not set and not enough samples)
  if (!pilot_adc_flag && (average_counter < PILOT_ADC_AVG)) {
    digitalWrite(7, HIGH);
    pwm_adc_value += analogRead(ADC_PWM);  //approx. 110us. But capuring should be a lot faster
    average_counter++;
    // ToDo: Just trigger a single conversion here, check for everything else in main
    digitalWrite(7, LOW);
  } else {
    // Signal that we've captured enough samples
    pilot_adc_flag = HIGH;
  }
}
