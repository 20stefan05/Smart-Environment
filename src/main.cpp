#include "RTOS.h"
#define TEMPERATURE 0
#define HUMIDITY 1
uint8_t last = TEMPERATURE;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  LoRa_Init();
#ifdef SOIL_MODULE
  //PumpInit();
  //Dallas_Init();
#endif
#ifdef AIR_MODULE
      //DHT_Init();
#endif
}
int currentTime = millis();
void loop()
{
  // put your main code here, to run repeatedly:
  if (millis() - currentTime >= SAMPLE_RATE)
  {
    currentTime = millis();
#ifdef SOIL_MODULE
    TaskSoilModule(last);
    last^=0x01;
#endif
#ifdef AIR_MODULE
    TaskAirModule(last);
    last^=0x01;
#endif
  }
}