extern bool letsGo;
#define BUTTON_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);
  TBB612FNG_init (); // Inicializar el controlador de motor
  QTR8A_init    (); // Inicializar los sensores QTR
  externals_init(); // Inicializar los pines y variables externas

}



void loop() {
  
  delay(300);
  if (digitalRead(BUTTON_PIN) == HIGH) {
    Serial.println("¡Boton presionado!");
    letsGo = true;
    while (letsGo){
    beginDrive(); // Iniciar el movimiento del robot
    delay(10); // Pequeño retraso para evitar saturar el loop
  }

  }

  else{
    Serial.println ("Esperando...");
    waitForButton(); // Esperar a que se presione el botón
  }

  }


