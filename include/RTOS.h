#ifndef RTOS_H
#define RTOS_H
#include "AirTempHumidity_Monitor.h"
#include "SoilTempMonitor.h"
#include "SoilMoistureMonitor.h"
#include "LoRaCommunication.h"
void TaskAirModule(uint8_t);
void TaskSoilModule(uint8_t);
#endif