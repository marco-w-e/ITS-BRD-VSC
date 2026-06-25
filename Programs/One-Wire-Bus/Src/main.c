/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "Typs.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "Output.h"
#include "Input.h"
#include "timer.h"
#include <stdint.h>
#include <stdio.h>
#include "fehler.h"
#include <string.h>



int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	initTimer();
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);
   oneWireSetup();
   
   
	                 // Initialisierung des LCD Boards mit Touch
    uint8_t rom[8];
	uint8_t ROM_NUM[4][8] ;
	

    uint8_t romCommand = 0x33;

    int fehler = 1;

    char str[16];
    char serial[16];
    char fam[16]; 
    float oldtem  = 0;
    uint8_t Lastdiscrepans = 0;
    uint8_t LastDeviceFlag = 0;

	
     /*
	int s = OW_searcht(ROM_NUM_1, &LastDeviceFlag, &Lastdiscrepans);
    snprintf(fam, sizeof(fam), "Fam: %u", ROM_NUM_1[0]);
    lcdPrintS(fam);
    lcdPrintS("\n");

    lcdPrintS("Serial: ");
    for (int i = 1; i < 7; i++)
    {
        snprintf(serial, sizeof(serial), "%u ", ROM_NUM_1[i]);
        lcdPrintS(serial);
    
	}
	snprintf(str, sizeof(str), "CRC: %u", ROM_NUM_1[7]);
    
    lcdPrintS(str);
    lcdPrintS("\n");
    int p = OW_searcht(ROM_NUM_1, &LastDeviceFlag, &Lastdiscrepans);
	
    lcdGotoXY(5, 8);
    snprintf(fam, sizeof(fam), "Fam: %u", ROM_NUM_1[0]);
    lcdPrintS(fam);
    lcdPrintS("\n");

    lcdPrintS("Serial: ");
    for (int i = 1; i < 7; i++)
    {
        snprintf(serial, sizeof(serial), "%u ", ROM_NUM_1[i]);
        lcdPrintS(serial);
    
	}
	snprintf(str, sizeof(str), "CRC: %u", ROM_NUM_1[7]);
    lcdPrintS(str);
    lcdPrintS("\n");

*/
int SenDa=0;
 OWFirst( Lastdiscrepans,  LastDeviceFlag);
 OW_searcht(rom, &LastDeviceFlag, &Lastdiscrepans);
 memcpy(ROM_NUM[0],rom,8);
for(int i = 1; i < 4;i++){
    
SenDa = OW_searcht(rom, &LastDeviceFlag, &Lastdiscrepans);
memcpy(ROM_NUM[i],rom,8);
}



float temperatur[4] ;


	//Test in Endlosschleife😮🥺
	while(1) {
        

        for(int i = 0; i < 4;i++){
    
            if(temperatur_lesen(ROM_NUM[i], & temperatur[i]) != WORKING){
                            lcdPrintS("Mess Fehler!\n");
                } 
        }
                    
                    
                    snprintf(str, sizeof(str), "tmp0: %f", temperatur[0]);
                    
                        lcdGotoXY(5, 5);
                        lcdPrintReplS(str);
                    
                    snprintf(str, sizeof(str), "tmp1: %f", temperatur[1]);
                    
                        lcdGotoXY(5, 6);
                        lcdPrintReplS(str);
                    
                    snprintf(str, sizeof(str), "tmp2: %f", temperatur[2]);
                   
                        lcdGotoXY(5, 7);
                        lcdPrintReplS(str);
                    
                    snprintf(str, sizeof(str), "tmp3: %f", temperatur[3]);
                    
                        lcdGotoXY(5, 8);
                        lcdPrintReplS(str);
                    
         impulsDelay(10000 * 90);
             
    } 
            
	
	
		
	
}


// EOF
