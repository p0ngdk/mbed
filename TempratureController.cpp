#include "mbed.h"
#include "headerFiles/temprature.h"


AnalogIn tempSensor(A0);

DigitalOut tempLed(D2);

int temp = 20.0f; 
float temperature;
int tempToUse = 30;

void convertTemp(){
    int readData;
    float resistance;
    readData = tempSensor.read_u16();
    resistance = (float) 10000.0 * ((65536.0 / readData) - 1.0);
    temperature = (1/((log(resistance/10000.0)/3975) + (1.0/298.15)))-273.15;
}

void tempThread(){
    while(true){
        int temp = int(temperature- 4);
        if(temp >= tempToUse){
            tempLed = 1;
        } else {
            tempLed = 0;
        }
    }
}