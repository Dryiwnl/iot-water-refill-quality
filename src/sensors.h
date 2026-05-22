#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

void iniciarSensores();

float lerDistanciaCM();

void lerTensoesAnalogicas2Min(float &tensaoPH, float &tensaoTurbidez);

float calcularPH(float tensao);
float calcularTurbidez(float tensao);

#endif