#include "PumpControl.h"
void PumpInit(){
    pinMode(PUMP_PIN, OUTPUT);
}
void PumpOpen(){
    digitalWrite(PUMP_PIN, HIGH);
}
void PumpClose(){
    digitalWrite(PUMP_PIN, LOW);
}
