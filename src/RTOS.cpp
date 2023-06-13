// #include "RTOS.h"
// void TaskAirModule(uint8_t sensor){
//     //LoRa_Send('A', 'T', DHT_GetTemp());
//     //LoRa_Send('A', 'H', DHT_GetHum());
//     if(sensor==0) LoRa_Send('A', 'T', DHT_GetTemp());
//     else if (sensor == 1) LoRa_Send('A', 'H', DHT_GetHum());
// }
// void TaskSoilModule(uint8_t sensor){
//     // LoRa_Send('S', 'T', Dallas_GetTemp());
//     // LoRa_Send('S', 'M', GetSoilMoist());
//     if(sensor==0) LoRa_Send('S', 'T', Dallas_GetTemp());
//    else if (sensor == 1) LoRa_Send('S', 'M', GetSoilMoist());
// }