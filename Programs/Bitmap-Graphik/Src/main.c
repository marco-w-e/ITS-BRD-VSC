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
#include <stdint.h>
#include "BMP_types.h"

uint16_t convertToRgb16(RGBTRIPLE farben){
		uint16_t farbe;
		farbe = (farben.rgbtRed >> 3 ) << 11;
		farbe |= (farben.rgbtGreen >> 2 ) << 5;
		farbe |= (farben.rgbtBlue>> 3 );
		return farbe;
	}
	

int main(void) {
	initITSboard(); // Initialisierung des ITS Boards
	initInput();   
	openNextFile();
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                        // Initialisierung des LCD Boards mit Touch
	
	
	

  // Begruessungstext	


	
	int x = 1;
	int y = 1;
	RGBTRIPLE farben;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;
	// Test in Endlosschleife
	COMread((char*)&FileHeader,sizeof(FileHeader),1); // bracuht noch einen errohandler 
	COMread((char*)&InfoHeader,sizeof(InfoHeader),1);	
	while(1) {
		
		for( int i = 0;i <= 9 ;i++){
			nextChar();

		}
		int start = nextChar();
		for( int i = 0;i <= start- 0xA ;i++){
			nextChar();

		}
			farben.rgbtBlue = nextChar();
			farben.rgbtGreen = nextChar();
			farben.rgbtRed= nextChar();
			nextChar();
		
		while (x != 400){ 
			
			Coordinate corrdinat;
			corrdinat.x = x;
			corrdinat.y = y;
			GUI_drawPoint(corrdinat,convertToRgb16(farben) ,DOT_PIXEL_1X1,DOT_FILL_AROUND );
			x++ ;

		}
		x = 0;
		y++;
	}
}

// EOF
