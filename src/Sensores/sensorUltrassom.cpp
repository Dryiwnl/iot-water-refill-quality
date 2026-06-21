#include <Arduino.h>

#define TRIG_PIN 5
#define ECHO_PIN 18

void iniciarUltrassom(){
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
}

float calcularDistancia(){
  float distancia_cm;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_PIN, LOW);

  float tempo = pulseIn(ECHO_PIN, HIGH);
  if(tempo == 0){
    Serial.println("Erro de leitura. Tente afastar mais o sensor.");
    return -1;
  }
  distancia_cm = (tempo * 0.0343)/2;
  return distancia_cm;
}

float lerUltrassom(){
  float ultrassom = calcularDistancia();
  return ultrassom;
}
