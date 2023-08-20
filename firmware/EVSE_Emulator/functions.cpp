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
  digitalWrite(LED_IDLE, status & STATE_IDLE);
  digitalWrite(LED_CONN, status & STATE_CONNECTED);
  digitalWrite(LED_CHRG, status & STATE_CHARGING);
  digitalWrite(LED_COOL, status & STATE_COOLING);
  digitalWrite(LED_CERR, status & STATE_CONERROR);
  digitalWrite(LED_ERR, status & STATE_ERROR);
}

void set_pwm(int width) {
  pinMode(3, OUTPUT);
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS22);
  OCR2A = 249;    // 249 = 1kHz
  OCR2B = width;  // 0...249 for 0...100% duty

  TIMSK2 = _BV(OCIE2A);  //enable OCR2A compare interrupt for ADC measurement. Also works with 100% duty.
}

int volt2state(float volt) {
  if ((volt >= (VOLT_IDLE - VOLT_WINDOW)) && (volt <= (VOLT_IDLE + VOLT_WINDOW))) {
    return STATE_IDLE;
  } else if ((volt >= (VOLT_CONNECTED - VOLT_WINDOW)) && (volt <= (VOLT_CONNECTED + VOLT_WINDOW))) {
    return STATE_CONNECTED;
  } else if ((volt >= (VOLT_CHARGING - VOLT_WINDOW)) && (volt <= (VOLT_CHARGING + VOLT_WINDOW))) {
    return STATE_CHARGING;
  } else if ((volt >= (VOLT_COOLING - VOLT_WINDOW)) && (volt <= (VOLT_COOLING + VOLT_WINDOW))) {
    return STATE_COOLING;
  } else if ((volt >= (VOLT_CONERROR - VOLT_WINDOW)) && (volt <= (VOLT_CONERROR + VOLT_WINDOW))) {
    return STATE_CONERROR;
  } else if ((volt >= (VOLT_ERROR - VOLT_WINDOW)) && (volt <= (VOLT_ERROR + VOLT_WINDOW))) {
    return STATE_ERROR;
  } else {
    return STATE_ERROR;
  }
}

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}