#define BUTTON_PIN 2
#define LEDBLINK   13


bool letsGo = false;
unsigned long lastBlinkTime = 0;
bool ledState = false;


// Funcion de espera.

void waitForButton() {
  for (int i = 0 ; i < 10 ; i++){
     if (millis() - lastBlinkTime > 500) {
      ledState = !ledState;
      digitalWrite(LEDBLINK, ledState ? HIGH : LOW);
      lastBlinkTime = millis();
    }
  }
}

void externals_init() {
   pinMode(LEDBLINK, OUTPUT);
   pinMode(BUTTON_PIN, INPUT);
   
 
}

