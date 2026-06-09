/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

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
int fehler =1;
int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	initTimer();
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);
   oneWireSetup();
   
	                 // Initialisierung des LCD Boards mit Touch
	uint8_t sensorSignal = 1;
	uint8_t romCommand = 0x33;
	uint64_t rom;
  // Begruessungstext	
	
	sensorSignal = reset();
	write_byte(romCommand);
	rom_read(&rom);
	lcdPrintInt(rom);

	// Test in Endlosschleife
	while(1) {
		
	}
}

// EOF
