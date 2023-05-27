#include "LoRaCommunication.h"
static RadioEvents_t RadioEvents;

char rxpacket[BUFFER_SIZE];
float txNumber;
int16_t rssi, rxSize;
bool lora_idle = true;
void OnTxDone(void);
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void OnTxTimeout(void);
void LoRa_Init()
{
    txNumber = 0;

    RadioEvents.TxDone = OnTxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    // RadioEvents.RxDone = OnRxDone;
    Radio.Init(&RadioEvents);
    Radio.SetChannel(RF_FREQUENCY);
    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, LORA_IQ_INVERSION_ON, 3000);
}
void LoRa_Send(uint8_t Place, uint8_t DataType, float value)
{
    // Places: S - Soil; A - Air
    // DataType: M-  Moisture; H - Humidity; T- temperature
    if (lora_idle == true)
    {
        // int8_t intval = (int8_t) value;
        // uint8_t txpacket[BUFFER_SIZE];
        // txpacket[0] = ID;
        // txpacket[1] = Place;
        // txpacket[2] = DataType;
        // txpacket[3] = (value<0) ? 1 : 0;
        // txpacket[4] = (uint8_t)abs(value);
        // txpacket[5] = (uint8_t)abs((value-intval)*100);
        // Serial.print(txpacket[0]);
        // Serial.print(txpacket[1]);
        // Serial.print(txpacket[2]);
        // Serial.print(txpacket[3]);
        // Serial.print(txpacket[4]);
        // Serial.print(txpacket[5]);
        // Serial.println();
        StaticJsonDocument<200> txpacket;
        String tp;
        switch(Place){
            case 'S': tp = "Soil "; break;
            case 'A': tp = "Air "; break;
        }
        switch(DataType){
            case 'H': tp += "Humidity"; break;
            case 'M': tp += "Moisture "; break;
            case 'T': tp += "Temperature "; break;
        }
        txpacket["id"] = ID;
        txpacket["type"] = tp;
        txpacket["value"] = value;
        char jsonBuffer[512];

        serializeJson(txpacket, jsonBuffer); // print to client
        Serial.println(String(jsonBuffer));

        Radio.Send((uint8_t*)jsonBuffer, strlen(jsonBuffer) ); // send the package out
        lora_idle = false;
    }
}
// void LoRa_Receive()
// {
//     if (lora_idle == true)
//     {
//         lora_idle = false;
//         Radio.Rx(0);
//     }
// }
void OnTxDone(void)
{
    Serial.println("TX done......");
    lora_idle = true;
}

void OnTxTimeout(void)
{
    Radio.Sleep();
    Serial.println("TX Timeout......");
    lora_idle = true;
}
// void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
// {
//     rssi = rssi;
//     rxSize = size;
//     memcpy(rxpacket, payload, size);
//     rxpacket[size] = '\0';
//     Radio.Sleep();
//     Serial.printf("\r\nreceived packet \"%s\" with rssi %d , length %d\r\n", rxpacket, rssi, rxSize);
//     lora_idle = true;
// }