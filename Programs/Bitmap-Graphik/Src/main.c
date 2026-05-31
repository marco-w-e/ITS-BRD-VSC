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
#include "BMP.h"
#include "input.h"
#include "button.h"



int main(void) {
	initITSboard();    						// Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 		// Initialisierung des LCD Boards mit Touch
	initInput();


	while(1) 
	{
		lcdGotoXY(10, 10);
		bmp_displayNext();
		wartenBisKnopfDruck();
	}

	return 0;
}

// EOF