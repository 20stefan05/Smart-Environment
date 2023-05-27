#ifndef AIR_MONITOR
#define AIR_MONITOR
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "Arduino.h"
#include "config.h"
#define DHTTYPE    DHT11     // DHT 11)
#define ERR -100
void DHT_Init();
float DHT_GetTemp();
float DHT_GetHum();
#endif