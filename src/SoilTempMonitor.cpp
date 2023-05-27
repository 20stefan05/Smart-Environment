#include "SoilTempMonitor.h"
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
void Dallas_Init(){
    sensors.begin();
}
float Dallas_GetTemp(){
    sensors.requestTemperatures(); 
    Serial.print("\nSoil temperature: ");
    Serial.print(sensors.getTempCByIndex(0));
    return sensors.getTempCByIndex(0);
}