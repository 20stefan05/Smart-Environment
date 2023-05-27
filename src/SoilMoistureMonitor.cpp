#include "SoilMoistureMonitor.h"
float GetSoilMoist(){
    return (float)analogRead(MOISTURE_SENSOR)/4096*100;
}