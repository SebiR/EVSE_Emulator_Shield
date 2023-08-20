#define LED_IDLE 8
#define LED_CONN 9
#define LED_CHRG 10
#define LED_COOL 11
#define LED_CERR 12
#define LED_ERR 13

void set_statusleds(int status);
void init_leds(void);
void set_pwm(int width);

enum STATUS {
  STATUS_IDLE = 0x01,
  STATUS_CONNECTED = 0x02,
  STATUS_CHARGING = 0x04,
  STATUS_COOLING = 0x08,
  STATUS_CONERROR = 0x10,
  STATUS_ERROR = 0x20
};

enum PWM_MODE {
  PWM_ALWAYS_ON = 249,  // 100% PWM for negotiation
  PWM_30A = 125         // 50% PWM equals 30A
};