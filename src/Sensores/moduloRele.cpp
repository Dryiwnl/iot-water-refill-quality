#include <Arduino.h>

#define RELE_PIN 23


//ATENÇÃO: A lógica do relé é negada, ou seja: HIGH = desligado e LOW = ligado
void iniciaRele(){
  //Define o pino como saída
  pinMode(RELE_PIN, OUTPUT);
  //inicia o relé desligado
  digitalWrite(RELE_PIN, HIGH);
}

void ligarRele(){
  digitalWrite(RELE_PIN, LOW);
}

void desligarRele(){
  digitalWrite(RELE_PIN, HIGH);
}