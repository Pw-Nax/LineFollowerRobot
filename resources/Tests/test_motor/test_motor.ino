#define AIN1 6
#define AIN2 7
#define PWMA 9

#define BIN1 11
#define BIN2 12
#define PWMB 10

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void loop() {
  // Motores hacia adelante
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 150);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 150);
  delay(2000);

  // Detener
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  delay(1000);

  // Motores hacia atrás
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 150);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 150);
  delay(2000);

  // Detener
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  delay(1000);
}
