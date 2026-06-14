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



int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	initTimer();
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);
   oneWireSetup();

   
	                 // Initialisierung des LCD Boards mit Touch
    uint8_t rom[8];
	uint8_t ROM_NUM_1[8] = { 0x28, 0xA7, 0x6D, 0xE6, 0x01, 0x00, 0x00, 0xD1 };
	uint8_t ROM_NUM_2[8] = { 0x28, 0x7D, 0x6D, 0xE6, 0x01, 0x00, 0x00, 0xDA };
	uint8_t ROM_NUM_3[8] = { 0x28, 0x64, 0x35, 0x89, 0x0D, 0x00, 0x00, 0x0D };
	uint8_t ROM_NUM_4[8] = { 0x28, 0x4E, 0x62, 0x89, 0x0D, 0x00, 0x00, 0x0C };

    uint8_t romCommand = 0x33;

    int fehler = 1;

    char str[16];
    char serial[16];
    char fam[16];


  // Begruessungstext	
	fehler = reset();
	
	    // ROM Command
    write_byte(romCommand);

    // ROM lesen
    if (rom_read(rom) != WORKING)
    {
        lcdPrintS("Read Error\n");
        while (1);
    }

    // CRC prüfen
    if (crc_pruefen(rom, 8) != WORKING)
    {
        lcdPrintS("CRC FAIL\n");
    }
    else
    {
        lcdPrintS("CRC OK\n");
    }

    // Ausgabe

    

    snprintf(fam, sizeof(fam), "Fam: %u", rom[0]);
    lcdPrintS(fam);
    lcdPrintS("\n");

    lcdPrintS("Serial: ");
    for (int i = 1; i < 7; i++)
    {
        snprintf(serial, sizeof(serial), "%u ", rom[i]);
        lcdPrintS(serial);
    
	}
	snprintf(str, sizeof(str), "CRC: %u", rom[7]);
    lcdPrintS(str);
    lcdPrintS("\n");


	uint64_t sensor_rom = 0;
    for (int i = 0; i < 8; i++) {
        sensor_rom |= ((uint64_t)rom[i] << (i * 8));
    }

	

	// Test in Endlosschleife
	while(1) {
		float temperatur = 0.0f;
	if(temperatur_lesen(rom, &temperatur) != WORKING){
		            lcdPrintS("Mess Fehler!\n");
	} else {
		snprintf(str, sizeof(str), "tmp: %f", temperatur);
    lcdPrintReplS(str);
	}
	impulsDelay(1000000);

	
		
	}
}


// EOF
