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
#include "input.h"


int main(void) {
	initITSboard(); // Initialisierung des ITS Boards
	initInput();   
	openNextFile();
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  // Begruessungstext	
	lcdPrintlnS("Hallo liebes TI-Labor (c-project)");
	int x = 1;
	int y = 1;

	// Test in Endlosschleife
	while(1) {
		
		while (x != 400){ 
			Coordinate corrdinat;
			corrdinat.x = x;
			corrdinat.y = y;
			GUI_drawPoint(corrdinat, 35000,DOT_PIXEL_1X1,DOT_FILL_AROUND );
			x++ ;

		}
		x = 0;
		y++;
	}
}

// EOF
