
#include "mbed.h"
#include "BSP_DISCO_F746NG/Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_lcd.h"
#include "BSP_DISCO_F746NG/Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_ts.h"


AnalogIn tempSensor(A0);
AnalogIn soundSensor(A1);

DigitalOut tempLed(D2);

int temp = 20.0f; 
float temperature;
int tempToUse = 30;
int currentBtnPressed;

Thread thread;
Thread soundT;

void convertTemp(){
    int readData;
    float resistance;
    readData = tempSensor.read_u16();
    resistance = (float) 10000.0 * ((65536.0 / readData) - 1.0);
    temperature = (1/((log(resistance/10000.0)/3975) + (1.0/298.15)))-273.15;
}


void soundThread(){
    while(true){
        float sound = soundSensor.read();
                wait_us(1000);

        printf("%i \n", int(sound * 100));
    }
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
void initDisplay(){
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_Clear(LCD_COLOR_BLACK);
}

void startThreads(){
    thread.start(tempThread);
    soundT.start(soundThread);
}

//main loop
int main()
{    
    TS_StateTypeDef TS_State;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;

    initDisplay();

    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

    startThreads();

    while (1) {
        convertTemp();


        char tempDisplay[25];
        sprintf(tempDisplay, "Temprature %i", int(temperature- 4));
        BSP_LCD_DisplayStringAt(0, 180, (uint8_t *)tempDisplay, CENTER_MODE);
        char tempToUseDisplay[25];
        sprintf(tempToUseDisplay, "Temprature %i", tempToUse);
        BSP_LCD_DisplayStringAt(2, 150, (uint8_t *)tempToUseDisplay, CENTER_MODE);

        //defining "buttons"
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_FillRect(100, 220, 50, 50);

        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_FillRect(220, 220, 50, 50);

        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_FillRect(340, 220, 50, 50);

        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_FillRect(400, 40, 20, 20);

        BSP_TS_GetState(&TS_State);

        if (TS_State.touchDetected) {

            x = TS_State.touchX[0];
            y = TS_State.touchY[0];
            
            sprintf((char*)text, "Touch %d: x=%d y=%d    ", idx+1, x, y);
            BSP_LCD_DisplayStringAt(0, LINE(idx+1), (uint8_t *)&text, LEFT_MODE);

            //defining button 1 pos
            if(x >= 100 && x <= 150 && y >= 220 && y <= 270){
                BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"indefor knap 1", CENTER_MODE);
                currentBtnPressed = 1;
            } else {   
            }

            //defining button 2 pos
            if(x >= 220 && x <= 270 && y >= 220 && y <= 270){
                BSP_LCD_DisplayStringAt(1, 150, (uint8_t *)"indefor knap 2", CENTER_MODE);
            } else {
            }

            //defining button 3 pos
            if(x >= 340 && x <= 390 && y >= 220 && y <= 390){
                BSP_LCD_DisplayStringAt(2, 50, (uint8_t *)"indefor knap 3", CENTER_MODE);
            } else {
            }

            if(x>= 400 && x<= 420 && y>= 70 && y<= 50){
                currentBtnPressed = 0;
                wait_us(1000);
                BSP_LCD_Clear(LCD_COLOR_BLACK);

            }
            
            switch(currentBtnPressed){
                case 1: {
                    BSP_LCD_FillRect(70, 70, 20, 20);
                    BSP_LCD_FillRect(110, 70, 20, 20);

                    if(x >= 70 && x <= 90 && y>= 70 && y<= 90 ){
                        BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
                        tempToUse--;
                    }
                    if(x>= 110 && x<= 130 && y>= 70 && y<= 90 ){
                        BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
                        tempToUse++;

                    }
                    break;
                }
            }
            }

    }

}

