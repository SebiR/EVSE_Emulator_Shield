#define LED_IDLE 8
#define LED_CONN 9
#define LED_CHRG 10
#define LED_COOL 11
#define LED_CERR 12
#define LED_ERR 13

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_IDLE, OUTPUT);
  pinMode(LED_CONN, OUTPUT);
  pinMode(LED_CHRG, OUTPUT);
  pinMode(LED_COOL, OUTPUT);
  pinMode(LED_CERR, OUTPUT);
  pinMode(LED_ERR, OUTPUT);
}

void loop() {
  digitalWrite(LED_ERR, LOW);
  digitalWrite(LED_IDLE, HIGH);
  delay(500); 

  digitalWrite(LED_IDLE, LOW);   
  digitalWrite(LED_CONN, HIGH);
  delay(500);   

  digitalWrite(LED_CONN, LOW);
  digitalWrite(LED_CHRG, HIGH);
  delay(500);

  digitalWrite(LED_CHRG, LOW);
  digitalWrite(LED_COOL, HIGH);
  delay(500);

  digitalWrite(LED_COOL, LOW);
  digitalWrite(LED_CERR, HIGH);
  delay(500);

  digitalWrite(LED_CERR, LOW);
  digitalWrite(LED_ERR, HIGH);
  delay(500);
}
