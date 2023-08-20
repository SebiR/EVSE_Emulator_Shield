#include "Arduino.h"
#include "config.h"

void init_leds() {
  pinMode(LED_IDLE, OUTPUT);
  pinMode(LED_CONN, OUTPUT);
  pinMode(LED_CHRG, OUTPUT);
  pinMode(LED_COOL, OUTPUT);
  pinMode(LED_CERR, OUTPUT);
  pinMode(LED_ERR, OUTPUT);
}

void set_statusleds(int status) {
  digitalWrite(LED_IDLE, status & STATUS_IDLE);
  digitalWrite(LED_CONN, status & STATUS_CONNECTED);
  digitalWrite(LED_CHRG, status & STATUS_CHARGING);
  digitalWrite(LED_COOL, status & STATUS_COOLING);
  digitalWrite(LED_CERR, status & STATUS_CONERROR);
  digitalWrite(LED_ERR, status & STATUS_ERROR);
}