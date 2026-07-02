#include <Arduino.h>

// Pino OUT do sensor de turbidez
#define TURB_PIN 32

// tensão medida em água limpa usada como referência para 0 NTU
float tensao_limpa = 2.062;

// ganho ajustável para transformar queda de tensão em turbidez
float ganho_turbidez = 1000.0;

void iniciarTurbidez(){
  pinMode(TURB_PIN, INPUT);
  analogReadResolution(12);
}

float lerTensaoTurbidez() {
  int adc = analogRead(TURB_PIN);
  float tensao = adc * 3.3 / 4095.0;
  return tensao;
}

float calcularNTU(float tensao) {
  float ntu = (tensao_limpa - tensao) * ganho_turbidez;

  if (ntu < 0) {
    ntu = 0;
  }
  return ntu;
}

float lerTurbidez(){
 float tensao = lerTensaoTurbidez();
 float turbidez = calcularNTU(tensao);
 return turbidez;
}