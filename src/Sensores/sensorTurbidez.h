#ifndef SENSOR_TURBIDEZ_H
#define SENSOR_TURBIDEZ_H

#include <Arduino.h>

void iniciarTurbidez();

float lerTensaoTurbidez();

float calcularNTU(float tensao);

float lerTurbidez();

#endif