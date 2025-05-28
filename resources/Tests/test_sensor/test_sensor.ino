#include <QTRSensors.h>

#define PIN_BOTON 2  // Botón conectado a D2 con resistencia pull-down
QTRSensors qtr;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BOTON, INPUT);  // Entrada normal (espera LOW o HIGH)

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A1, A2, A3, A4, A5, A6}, SensorCount);
  qtr.setEmitterPin(LED_BUILTIN);

  delay(500);
  Serial.println("Esperando presionar el botón para iniciar lectura...");
}

void loop() {
  // Espera a que se presione el botón (HIGH = presionado)
  if (digitalRead(PIN_BOTON) == LOW) {
    Serial.println("¡Botón presionado! Iniciando lectura de sensores...");
    delay(300);  // Anti-rebote

    while (digitalRead(PIN_BOTON) == LOW) {
      qtr.read(sensorValues);
      for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print("S");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(sensorValues[i]);
        Serial.print("\t");
      }
      Serial.println();
      delay(200);
    }

    Serial.println("Lectura detenida.");
  }
}
