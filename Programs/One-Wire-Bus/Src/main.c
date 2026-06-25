/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "Input.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "Output.h"
#include "Typs.h"
#include "additionalFonts.h"
#include "error.h"
#include "fehler.h"
#include "fontsFLASH.h"
#include "init.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  initITSboard(); // Initialisierung des ITS Boards
  initTimer();
  GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
  TP_Init(false);
  oneWireSetup();

  // Initialisierung des LCD Boards mit Touch
  uint8_t rom[8];
  uint8_t ROM_NUM[5][8];

  char str[16];

  uint8_t Lastdiscrepans = 0;
  uint8_t LastDeviceFlag = 0;
  float temperatur[4];
  int sensorCount = 0;
  

  
  while (1) {

    int da = OW_searcht(rom, &LastDeviceFlag, &Lastdiscrepans);

    if(da == -2){
        break;
    }
    memcpy(ROM_NUM[sensorCount], rom, 8);
    sensorCount++;
  
  }
  /*
  for (int i = 1; i < 4; i++) {

    SenDa = OW_searcht(rom, &LastDeviceFlag, &Lastdiscrepans);
    memcpy(ROM_NUM[i], rom, 8);
  }
*/
  for (int i = 0; i < 5; i++) {

    if (ROM_NUM[i][1] != 0) {
      lcdGotoXY(0, i);
      snprintf(str, sizeof(str), "%u", i);

      lcdPrintS("SensorTMP ");
      lcdPrintS(str);

      
    }
  }

  for(int  i = 0; i < sensorCount; i++){
    lcdGotoXY(0, i+10);
    snprintf(str, sizeof(str), "%u", i);
    lcdPrintS("ROM ");
    lcdPrintS(str);
    lcdPrintS(" ");

    for(int j = 0; j < 8 ; j++){
        snprintf(str, sizeof(str), "%02X ", ROM_NUM[i][j]);
        lcdPrintS(str);
    }
}




  // Test in Endlosschleife😮🥺
  while (1) {

    for (int i = 0; i < sensorCount; i++) {
      if (temperatur_lesen(ROM_NUM[i], &temperatur[i]) != WORKING) {
        lcdGotoXY(0, i);
        lcdPrintS("Mess Fehler!\n");
      }

      snprintf(str, sizeof(str), "%f", temperatur[i]);
      lcdGotoXY(13, i);
      lcdPrintReplS(str);
    }
  }
}

// EOF
