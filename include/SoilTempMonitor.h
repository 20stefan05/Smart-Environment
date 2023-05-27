#ifndef SOIL_MONITOR
#define SOUL_MONITOR
#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "config.h"

void Dallas_Init();
float Dallas_GetTemp();
#endif