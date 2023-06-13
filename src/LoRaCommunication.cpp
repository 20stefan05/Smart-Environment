#include "LoRaCommunication.h"


#define airModule 0
#define soilModule 1
static RadioEvents_t RadioEvents;

char rxpacket[BUFFER_SIZE];
float txNumber;
int16_t Rssi, rxSize;
bool lora_idle = true;
bool lora_tx = false;
void OnTxDone(void);
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void OnTxTimeout(void);


void LoRa_Init()
{
    txNumber = 0;
    Rssi = 0;
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxDone = OnRxDone;

    Radio.Init(&RadioEvents);
    Radio.SetChannel(RF_FREQUENCY);
    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, LORA_IQ_INVERSION_ON, 3000);
    Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                      LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                      LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                      0, true, 0, 0, LORA_IQ_INVERSION_ON, true);
}
extern float airTemperature, airHumidity, soilTemperature, soilMoisture;
extern uint8_t moduleType;
void LoRa_Send()
{
    if (lora_idle == true)
    {
        StaticJsonDocument<200> txpacket;
        txpacket["Id"] = ID;
        if(moduleType == airModule){
            txpacket["AirTemperature"] = airTemperature;
            txpacket["AirHumidity"] = airHumidity;
        }
        else if(moduleType == soilModule){
            txpacket["SoilTemperature"] = soilTemperature;
            txpacket["SoilMoisture"] = soilMoisture;
        }
        char jsonBuffer[512];

        serializeJson(txpacket, jsonBuffer); // print to client
        Serial.println(String(jsonBuffer));

        Radio.Send((uint8_t *)jsonBuffer, strlen(jsonBuffer)); // send the package out
        lora_idle = false;
    }
}

void LoRa_Receive()
{
    if (lora_idle == true)
    {
        lora_idle = false;
        Radio.Rx(0);

    }
}
void OnTxDone(void)
{
    Serial.println("TX done......");
    turnOffRGB();
    lora_tx = false;
    lora_idle = true;
}

void OnTxTimeout(void)
{
    Radio.Sleep();
    Serial.println("TX Timeout......");
    lora_idle = true;
}
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
    Rssi = rssi;
    rxSize = size;
    memcpy(rxpacket, payload, size);
    rxpacket[size] = '\0';
    turnOnRGB(COLOR_RECEIVED, 0);
    Radio.Sleep();

    Serial.printf("\r\nreceived packet \"%s\" with Rssi %d , length %d\r\n", rxpacket, Rssi, rxSize);
    DynamicJsonDocument doc(BUFFER_SIZE);
    deserializeJson(doc, rxpacket);
    if (doc["Id"] == ID && doc["RelayState"] == 0){
        PumpClose();
        lora_tx = true;
    }
    else if (doc["Id"] == ID && doc["RelayState"] == 1){
        PumpOpen();
        lora_tx = true;
    }
    else if (doc["Id"] == ID && doc["Transmit"] == 1)
        lora_tx = true;
    lora_idle = true;
}