#include "mbed.h"
#include "BSP_DISCO_F746NG/Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_lcd.h"
#include "BSP_DISCO_F746NG/Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_ts.h"
#include "headerFiles/display.h"
#include "headerFiles/sound.h"
#include "headerFiles/temprature.h"

int currentBtnPressed;

extern float temperature;
extern int tempToUse;
bool dev = false;
int roomID = 1;

void initDisplay(){
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_Clear(LCD_COLOR_BLACK);
}

 //defining "buttons"
void defineButtons(){ 
    BSP_LCD_SetTextColor(LCD_COLOR_RED);

    BSP_LCD_FillRect(100, 220, 50, 50);
    BSP_LCD_FillRect(220, 220, 50, 50);
    BSP_LCD_FillRect(340, 220, 50, 50);

    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    
    BSP_LCD_FillRect(400, 40, 20, 20);

}


//thread that handles the displaying of buttons and handle touch
void displayThread(){
    //defining variables
    TS_StateTypeDef TS_State;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;
    
    //setups display
    initDisplay();
    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

    while(true){

        defineButtons();

        //sets the temprature and temptouse on the display 
        char tempDisplay[25];
        sprintf(tempDisplay, "Current temprature %i", int(temperature- 4));
        BSP_LCD_DisplayStringAt(0, 180, (uint8_t *)tempDisplay, LEFT_MODE);
        char tempToUseDisplay[25];
        sprintf(tempToUseDisplay, "Recommended temprature %i", tempToUse);
        BSP_LCD_DisplayStringAt(2, 150, (uint8_t *)tempToUseDisplay, LEFT_MODE);


        //gets touch state
        BSP_TS_GetState(&TS_State);

        if (TS_State.touchDetected) {

            x = TS_State.touchX[0];
            y = TS_State.touchY[0];

            if(dev){
                //used for testing
                sprintf((char*)text, "Touch %d: x=%d y=%d    ", idx+1, x, y);
                BSP_LCD_DisplayStringAt(0, LINE(idx+1), (uint8_t *)&text, LEFT_MODE);
            } else {
                char room[25];
                sprintf(room, "RoomID %i", roomID);
                BSP_LCD_DisplayStringAt(0, LINE(idx+1), (uint8_t *)room, LEFT_MODE);
            }


            //defining button 1 pos
            if(x >= 100 && x <= 150 && y >= 220 && y <= 270){
                //displays temprature on screen and what temperature to use
                currentBtnPressed = 1;
            } else {

            }

            //defining button 2 pos
            if(x >= 220 && x <= 270 && y >= 220 && y <= 270){

                currentBtnPressed = 2;
                
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
                case 2: {
                    BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"indefor knap 1", CENTER_MODE);

                    break;
                }
                }
            }
        }
    }
}