#include "LoRaCommunication.h"
#include "SoilMoistureMonitor.h"
#include "SoilTempMonitor.h"
#include "AirTempHumidity_Monitor.h"

int moduleType = soilModule;

extern bool lora_tx;
float airTemperature, airHumidity, soilTemperature, soilMoisture;
void updateSoilSensors(float *soilTemperature, float *soilMoisture);
void updateAirSensors(float *airTemperature, float *airHumidity);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  LoRa_Init();
  if (moduleType == soilModule)
  {
    PumpInit();
    Dallas_Init();
  }
  else if (moduleType == airModule)
  {
    DHT_Init();
  }
}
void loop()
{
  if (!lora_tx)
  {
    LoRa_Receive();
  }
  else if (lora_tx)
  {
    LoRa_Send();
  }
  if (moduleType == soilModule)
  {
    updateSoilSensors(&soilTemperature, &soilMoisture);
  }
  else if (moduleType == airModule)
  {
    updateAirSensors(&airTemperature, &airHumidity);
  }
}
void updateSoilSensors(float *soilTemperature, float *soilMoisture)
{
  *soilTemperature = Dallas_GetTemp();
  *soilMoisture = GetSoilMoist();
}
void updateAirSensors(float *airTemperature, float *airHumidity)
{
  *airTemperature = DHT_GetTemp();
  *airHumidity = DHT_GetHum();
}