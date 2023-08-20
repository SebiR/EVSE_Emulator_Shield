#include "config.h"

void setup() {

  Serial.begin(9600);
  init_leds();

  Serial.println("EVSE Emulator 1.0");

  set_pwm(PWM_30A);

}

void loop() {
  
  set_statusleds(STATUS_IDLE);
  delay(500); 

  set_statusleds(STATUS_CONNECTED);
  delay(500); 

  set_statusleds(STATUS_CHARGING);
  delay(500);

  set_statusleds(STATUS_COOLING);
  delay(500);  

  set_statusleds(STATUS_CONERROR);
  delay(500); 

  set_statusleds(STATUS_ERROR);
  delay(500); 
}


// Timer Compare A Interrupt vector, called with rising edge of PWM
// Used for ADC measurement during high cycle
ISR(TIMER2_COMPA_vect) { // called by timer2
  delayMicroseconds(50); // wait for value to stabilize
  // Do ADC measurement here
}
