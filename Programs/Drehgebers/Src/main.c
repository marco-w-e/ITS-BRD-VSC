/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    main.c
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

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
#include "rechner.h"




int main(void) {
	initITSboard(); 
	GUI_init(DEFAULT_BRIGHTNESS);
	TP_Init(false);
	int phase;
	int oldPhase =0;
	 Direction currentDirection;
	   // Initialisierung des ITS Boards      // Initialisierung des LCD Boards mit Touch
	// Test in Endlosschleife
	while(1) {
		phase =gpioAusLesen();
		LCDprintint(phase);
		getDirection(oldPhase,phase,&currentDirection);
		oldPhase = phase;
		lcdPrintS(directionName[currentDirection]);
	}
}

// EOF
