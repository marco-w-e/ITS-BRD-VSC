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


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	initTimer();
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  // Begruessungstext	
	
	pd1High();
	// Test in Endlosschleife
	while(1) {
		pd0High();
		impulsDelay(100000 * TICKS_PER_US);
		pd0Low();
		impulsDelay(100000 * TICKS_PER_US);
	}
}

// EOF
