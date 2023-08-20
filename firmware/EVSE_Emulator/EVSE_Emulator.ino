#include "config.h"

volatile int pwm_adc_value = 0;
int fsm_state = STATE_IDLE;

void setup() {

  Serial.begin(9600);
  init_leds();

  Serial.println("EVSE Emulator 1.0");

  set_pwm(PWM_30A);
}

void loop() {

  set_statusleds(fsm_state);

  switch (fsm_state) {
    case STATE_IDLE:
      Serial.println("FSM: IDLE");
      fsm_state = STATE_CONNECTED;
      break;
    case STATE_CONNECTED:
      Serial.println("FSM: CONNECTED");
      fsm_state = STATE_CHARGING;
      break;
    case STATE_CHARGING:
      Serial.println("FSM: CHARGING");
      fsm_state = STATE_COOLING;
      break;
    case STATE_COOLING:
      Serial.println("FSM: COOLING");
      fsm_state = STATE_CONERROR;
      break;
    case STATE_CONERROR:
      Serial.println("FSM: CONNECTION ERROR");
      fsm_state = STATE_ERROR;
      break;
    case STATE_ERROR:
      Serial.println("FSM: ERROR");
      fsm_state = STATE_IDLE;
      break;
    default:
      Serial.println("FSM: We should not be here...");
      fsm_state = STATE_ERROR;
      break;
  }

  delay(500);
}


// Timer Compare A Interrupt vector, called with rising edge of PWM
// Used for ADC measurement during high cycle
ISR(TIMER2_COMPA_vect) {                // called by timer2
  delayMicroseconds(50);                // wait for value to stabilize
  pwm_adc_value = analogRead(ADC_PWM);  //approx. 110us
  // ToDo: Just trigger a single conversion here, check for everything else in main
}
