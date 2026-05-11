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
#include "display.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "stdio.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "Stack.h"
#include "Keypad.h"
#include "token.h"
#include "Fehler.h"
#include "scanner.h"
#include "error.h"
#include "rechner.h"


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	initDisplay();
	
	

  // Begruessungstext	
	makeKeyPad();

	// Test in Endlosschleife
	while(1) {
	 T_token input = nextToken();
   switch (input.tok) {
      case PLUS:refresh (plus());
      break;
      case MINUS:refresh( minus());
      break; 
      case MULT:refresh( mal());
      break;   
      case DIV: refresh(geteilt());
      break;
      case PRT:refresh(printZeichen());
      break;
      case SWAP: refresh(swap());
      break;
      case PRT_ALL: refresh(printAlles());
      break; 
      case DOUBLE: refresh(verdoppleTop() );
      break;
		  case CLEAR: refresh(clear());
      break;
      case NUMBER: refresh(push(&input.val));
      break;
      case OVERFLOW: refresh(INT_OVERFLOW); 
      break;
   }
	
	}
}


// EOF
