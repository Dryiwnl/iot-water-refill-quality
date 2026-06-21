#ifndef SENSOR_PH_H
#define SENSOR_PH_H

#include <Arduino.h>

void iniciarpH();

int lerADCFiltrado();

float lerTensaoPH();

float calcularPH(float tensao);

float lerPH();

#endif