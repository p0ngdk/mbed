#include "mbed.h"
#include "BSP_DISCO_F746NG/Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_lcd.h"
#include "BSP_DISCO_F746NG/Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_ts.h"
#include "headerFiles/temprature.h"
#include "DHT.h"




AnalogIn tempSensor(A0);
DHT THSensor(D8, DHT22);


DigitalOut tempLed(D2);

int temp = 20.0f; 

float temperature;
int tempToUse = 30;
int h;

//convert analog signal to celsius  !!!! formel taken from internet !!!!
void convertTemp(){
    int readData;
    float resistance;
    readData = tempSensor.read_u16();
    resistance = (float) 10000.0 * ((65536.0 / readData) - 1.0);
    temperature = (1/((log(resistance/10000.0)/3975) + (1.0/298.15)))-273.15;
}


//turns light on and of when temp is higher that the temptouse 
void tempThread(){
    while(true){
        convertTemp();

        int temp = int(temperature- 4);
        if(temp >= tempToUse){
            tempLed = 1;
        } else {
            tempLed = 0;
        }
        THSensor.readData();
         h = THSensor.ReadHumidity();
        //printf("humidity: %i \n", h);
        char humidityDisplay[25];
        sprintf(humidityDisplay, "humidity: %i", h);
        BSP_LCD_DisplayStringAt(2, 100, (uint8_t *)humidityDisplay, LEFT_MODE);
    }
}