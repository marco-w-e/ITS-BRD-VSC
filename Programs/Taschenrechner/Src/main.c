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
  char str[20];
	
	// Test in Endlosschleife
	while(1) {
	 T_token input = nextToken();
   switch (input.tok) {
      case PLUS: plus();
      break;
      case MINUS: minus();
      break; 
      case MULT: mal();
      break;   
      case DIV: geteilt();
      break;
      case PRT:printZeichen();
      break;
      case SWAP: swap();
      break;
      case PRT_ALL: printAlles();
      break; 
      case DOUBLE: ;
      break;
		  case CLEAR: clear();
      break;
      default: push(&input.val);
                
   }
	
	}
}


// EOF
