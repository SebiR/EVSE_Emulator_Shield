#define LED_IDLE 8
#define LED_CONN 9
#define LED_CHRG 10
#define LED_COOL 11
#define LED_CERR 12
#define LED_ERR 13

void set_statusleds(int status);
void init_leds();

enum STATUS {
  STATUS_IDLE = 0x01,
  STATUS_CONNECTED = 0x02,
  STATUS_CHARGING = 0x04,
  STATUS_COOLING = 0x08,
  STATUS_CONERROR = 0x10,
  STATUS_ERROR = 0x20
};