#include "mbed.h"
#include "BSP_DISCO_F746NG/Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_lcd.h"
#include "BSP_DISCO_F746NG/Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_ts.h"
#include "headerFiles/display.h"



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

    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillRect(220, 220, 50, 50);

    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillRect(340, 220, 50, 50);

    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect(400, 40, 20, 20);

}