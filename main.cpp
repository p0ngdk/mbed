
#include "mbed.h"
#include "BSP_DISCO_F746NG/Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_lcd.h"
#include "BSP_DISCO_F746NG/Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_ts.h"
#include "headerFiles/display.h"
#include "headerFiles/sound.h"
#include "headerFiles/temprature.h"

int currentBtnPressed;

Thread thread;
Thread soundT;


void startThreads(){
    thread.start(tempThread);
    soundT.start(soundThread);
}

//main loop
int main()
{    
    //defining variables
    TS_StateTypeDef TS_State;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;

    //setups display
    initDisplay();
    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

    //starts threads
    startThreads();

    while (1) {
        // convert analog signal to temprature
        convertTemp();
    
        defineButtons();

        char tempDisplay[25];
        sprintf(tempDisplay, "Current temprature %i", int(temperature- 4));
        BSP_LCD_DisplayStringAt(0, 180, (uint8_t *)tempDisplay, CENTER_MODE);
        char tempToUseDisplay[25];
        sprintf(tempToUseDisplay, "Recommended temprature %i", tempToUse);
        BSP_LCD_DisplayStringAt(2, 150, (uint8_t *)tempToUseDisplay, CENTER_MODE);

        BSP_TS_GetState(&TS_State);

        if (TS_State.touchDetected) {

            x = TS_State.touchX[0];
            y = TS_State.touchY[0];
            
            //used for testing
            sprintf((char*)text, "Touch %d: x=%d y=%d    ", idx+1, x, y);
            BSP_LCD_DisplayStringAt(0, LINE(idx+1), (uint8_t *)&text, LEFT_MODE);

            //defining button 1 pos
            if(x >= 100 && x <= 150 && y >= 220 && y <= 270){
                //displays temprature on screen and what temperature to use
                currentBtnPressed = 1;
            } else {

            }

            //defining button 2 pos
            if(x >= 220 && x <= 270 && y >= 220 && y <= 270){
                BSP_LCD_DisplayStringAt(1, 150, (uint8_t *)"indefor knap 2", CENTER_MODE);
            }

            
            //defining button close pos
            if(x >= 400 && x<= 420 && y>= 40 && y<= 70){
                currentBtnPressed = 0;
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

