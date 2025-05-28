#include <QTRSensors.h>
#define EMITTER_PIN 13
QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

// Variables para el PID
// PID
float KP = 0.01;
float KD = 1.0;
float Ki = 0.006;
int Velmax = 80;

// Integral
int error1 = 0, error2 = 0, error3 = 0, error4 = 0, error5 = 0, error6 = 0;

// Inicializar PID variables
unsigned int position = 0;   // Posición del robot
int proporcional = 0;        // Error proporcional
int integral = 0;            // Error integral
int derivativo = 0;          // Error derivativo
int last_prop = 0;           // Último error proporcional
int Target = 2500;           // Valor objetivo para el PID
bool calibration = true;

void QTR8A_init (){
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A1, A2, A3, A4, A5, A6}, SensorCount);
  qtr.setEmitterPin(EMITTER_PIN);
}


void beginDrive (){
  if (calibration){
  Serial.println ("Calibrar");
  for (int i = 0; i < 70; i++) {
    digitalWrite(EMITTER_PIN, HIGH); delay(20);
    qtr.calibrate();
    digitalWrite(EMITTER_PIN, LOW); delay(20);
  } 
  calibration = false;
  }
  

  digitalWrite (EMITTER_PIN, HIGH);
// Leer sensores
  qtr.read(sensorValues);
  position = qtr.readLineBlack(sensorValues);

  proporcional = ((int)position) - Target;

  if (proporcional <= -Target) {
    Motorde(0);
    freno(true, false, 255);
  } else if (proporcional >= Target) {
    Motoriz(0);
    freno(false, true, 255);
  }

  derivativo = proporcional - last_prop; 
  integral = error1 + error2 + error3 + error4 + error5 + error6;
  last_prop = proporcional;

  error6 = error5;
  error5 = error4;  
  error4 = error3;  
  error3 = error2;
  error2 = error1;
  error1 = proporcional;

  int diferencial = (proporcional * KP) + (derivativo * KD) + (integral * Ki);

  if (diferencial > Velmax) diferencial = Velmax; 
  else if (diferencial < -Velmax) diferencial = -Velmax;

  int velIzq, velDer;

  if (diferencial < 0) {
    velIzq = Velmax + diferencial;
    velDer = Velmax;
  } else {
    velIzq = Velmax;
    velDer = Velmax - diferencial;
  }

  Motor(velIzq, velDer);

  Serial.print("Posicion: "); Serial.print(position);
  Serial.print(" | Prop: "); Serial.print(proporcional);
  Serial.print(" | Deriv: "); Serial.print(derivativo);
  Serial.print(" | Int: "); Serial.print(integral);
  Serial.print(" | Diff: "); Serial.print(diferencial);
  Serial.print(" | Vel L/R: "); Serial.print(velIzq); Serial.print("/"); Serial.println(velDer);

  delay(200);

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