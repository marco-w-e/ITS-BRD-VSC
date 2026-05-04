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
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "input.h"
#include "display.h"





int main(void) {
	initITSboard(); 
	GUI_init(DEFAULT_BRIGHTNESS);
	TP_Init(false);
	int phase;
	int oldPhase =0;

	   // Initialisierung des ITS Boards      // Initialisierung des LCD Boards mit Touch
	// Test in Endlosschleife
	while(1) {
		phase =gpioAusLesen();
		LCDprintint(phase);
		oldPhase = phase;
		
	}
}

// EOF
