// Definicion de pines para el puente H TB6612FNG
#define AIN1   6   
#define AIN2   7 
#define PWMA   9 

#define BIN1   11 
#define BIN2   12  
#define PWMB   10 



void TBB612FNG_init() {
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
}



void Motoriz(int value) {
  if (value >= 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    value *= -1;
  }
  analogWrite(PWMB, value);
}

void Motorde(int value) {  
  if (value >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    value *= -1;
  }    
  analogWrite(PWMA, value);
}

void Motor(int left, int right) {
  Motoriz(left);
  Motorde(right);
}

void freno(boolean left, boolean right, int value) {
  if (left) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, value);
  }
  if (right) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, value);
  }
}