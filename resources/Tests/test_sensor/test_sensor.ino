#include <QTRSensors.h>

#define PIN_BOTON 2  // Botón en D2 con pull-down
#define EMITTER_PIN LED_BUILTIN  // Cambiá si usás otro pin

QTRSensors qtr;
const uint8_t SensorCount = 5;  // Solo 5 sensores (A2 a A6)
uint16_t sensorValues[SensorCount];

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BOTON, INPUT);  // Asumimos resistencia pull-down
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A2, A3, A4, A5, A6}, SensorCount);
  qtr.setEmitterPin(EMITTER_PIN);

  delay(500);
  Serial.println("Presioná el botón para iniciar prueba de Target...");
}

void loop() {
  if (digitalRead(PIN_BOTON) == HIGH) {
    Serial.println("Leyendo sensores y posición...");
    delay(300);  // Anti-rebote

    while (digitalRead(PIN_BOTON) == HIGH) {
      digitalWrite(EMITTER_PIN, HIGH);  // Encender LEDs del QTR

      qtr.read(sensorValues);
      uint16_t position = qtr.readLineBlack(sensorValues);

      // Mostrar posición y valores
      Serial.print("Position: ");
      Serial.print(position);
      Serial.print(" | ");

      for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print("S");
        Serial.print(i + 2);  // A2=Sensor físico 2
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
