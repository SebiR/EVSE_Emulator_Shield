#include "config.h"

void setup() {

  Serial.begin(9600);
  init_leds();

  Serial.println("EVSE Emulator 1.0");

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
