#include "SoilMoistureMonitor.h"
float GetSoilMoist(){
    return (float)analogRead(MOISTURE_SENSOR)/MAX_SOIL_MOISTURE_ADC*100;
}