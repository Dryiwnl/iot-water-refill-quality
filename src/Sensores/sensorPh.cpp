#include <Arduino.h>

#define PH_PIN 34

//ATENÇÃO: esse valor pode ser alterado de acordo com a demanda, pois com o tempo, o módulo 4502C de pH perde a calibração
//potanto caso o código não retorne algo em torno de 7.00 a calibração deve ser feita novamente
//tensao_ph7 representa a tensão medida na água usada como referência para pH 7
float tensao_ph7 = 2.200;

//Ganho aumentado para ampliar diferenças pequenas de tensão
float slope = -30.0;

//A documentação pede para que uma leitura demore no mínimo 2min para a sonda estabilizar. Nesse caso colocamos 1min a mais
//por precaução, porém, tabém pode ser alterado de acordo com a demanda (contando que TEMPO_TESTE>=2min)
const unsigned long TEMPO_TESTE = 180000; // 3 minutos

//Intervalo entre as leituras
const unsigned long INTERVALO_LEITURA = 1000; // 1 segundo

//vetor de 10 posições e a auxiliar tempo serão utilizadas para filtrar a minha leitura
int buffer_arr[10], temp;

void iniciarpH(){
  analogReadResolution(12);
  analogSetPinAttenuation(PH_PIN, ADC_11db);
}

//como o sensor oscila muito nas leituras, fazemos 10 leituras, e armazenamos no vetor
int lerADCFiltrado() {
  for (int i = 0; i < 10; i++) {
    buffer_arr[i] = analogRead(PH_PIN);
    delay(30);
  }

  // Ordena os valores
  //loop para iterar entre a primeira leitura e a penultima
  for (int i = 0; i < 9; i++) {
  //verificação de todos os elementos depois de i até o final para deixar em ordem crescente
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }

  long soma = 0;

  //de todos os dez valores, os dois maiores e menores são descartados, ou seja, buffer_arr = [0,1,2,3,4,5,7,8,9,10]
  for (int i = 2; i < 8; i++) {
    soma += buffer_arr[i];
  }
  //retorna a média
  return soma / 6;
}

float lerTensaoPH() {
  // adc recebe a média das melhores leituras
  int adc = lerADCFiltrado();

  //conversão do adc em tensão:
  //adc tem 2^12 = 4096, ou seja 4095 valores 0-4095
  //tensão do esp é de 3,3V
  float tensao = adc * 3.3 / 4095.0;

  return tensao;
}

float calcularPH(float tensao) {
  //fórmula da conversão de tensão em pH
  float ph = 7 + slope * (tensao - tensao_ph7);

  if (ph < 0) {
    ph = 0;
  }
  if (ph > 14) {
    ph = 14;
  }
  return ph;
}

float lerPH(){
  float tensao = lerTensaoPH();
  float ph = calcularPH(tensao);

  Serial.print("Tensao pH: ");
  Serial.print(tensao, 3);
  Serial.print(" V | pH: ");
  Serial.println(ph, 2);

  return ph;
}