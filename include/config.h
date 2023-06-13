#ifndef CONFIG_H
#define CONFIG_H
#define DHTPIN GPIO1
#define PUMP_PIN GPIO3
#define ONE_WIRE_BUS GPIO2
#define MOISTURE_SENSOR ADC

#define ID 1

#define airModule 0
#define soilModule 1


#define MAX_SOIL_MOISTURE_ADC 4096

#define SAMPLE_RATE 1000
#define SAMPLES_NR_OF 100

#define LORA_RX_TIMEOUT 100

#define TIME_TILL_SLEEP 5000
#define TIME_TILL_WAKEUP 5000
#endif