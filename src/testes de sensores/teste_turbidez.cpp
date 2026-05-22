#include <Arduino.h>

// Pino OUT digital do sensor de turbidez
#define TURB_PIN 32

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(TURB_PIN, INPUT);

  Serial.println("=== Teste Digital Sensor de Turbidez ===");
  Serial.println("Ligacao:");
  Serial.println("VCC -> VIN/5V");
  Serial.println("GND -> GND");
  Serial.println("OUT -> GPIO32");
  Serial.println();
  Serial.println("Ajuste o trimpot ate o sensor mudar de estado quando bloquear a luz.");
  Serial.println();
}

void loop() {
  int estado = digitalRead(TURB_PIN);

  Serial.print("Estado digital do OUT: ");

  if (estado == HIGH) {
    Serial.println("HIGH");
  } else {
    Serial.println("LOW");
  }

  delay(300);
}