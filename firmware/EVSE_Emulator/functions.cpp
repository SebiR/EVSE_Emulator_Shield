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

void set_pwm(int width) {
  pinMode(3, OUTPUT);
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS22);
  OCR2A = 249; // 249 = 1kHz
  OCR2B = width; // 0...249 for 0...100% duty

  TIMSK2 = _BV(OCIE2A); //enable OCR2A compare interrupt for ADC measurement. Also works with 100% duty.
}