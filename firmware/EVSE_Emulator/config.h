#define LED_IDLE 8
#define LED_CONN 9
#define LED_CHRG 10
#define LED_COOL 11
#define LED_CERR 12
#define LED_ERR 13

#define ADC_PWM 0
#define ADC_PP 1

void set_statusleds(int status);
void init_leds(void);
void set_pwm(int width);

enum STATE {
  STATE_IDLE = 0x01,
  STATE_CONNECTED = 0x02,
  STATE_CHARGING = 0x04,
  STATE_COOLING = 0x08,
  STATE_CONERROR = 0x10,
  STATE_ERROR = 0x20
};

enum PWM_MODE {
  PWM_ALWAYS_ON = 249,  // 100% PWM for negotiation
  PWM_30A = 125         // 50% PWM equals 30A
};