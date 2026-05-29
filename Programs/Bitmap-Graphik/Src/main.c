/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "MS_basetypes.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"

#include "input.h"
#include <stdint.h>
#include "BMP_types.h"

#define MAX_BREITE 480
#define MAX_HÖHE   320

uint16_t convertToRgb16(RGBQUAD farben){
		uint16_t farbe;
		farbe = (farben.rgbRed >> 3 ) << 11;
		farbe |= (farben.rgbGreen >> 2 ) << 5;
		farbe |= (farben.rgbBlue>> 3 );
		return farbe;
	}

	

int main(void) {
	initITSboard(); // Initialisierung des ITS Boards
	initInput();   
	openNextFile();
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                        // Initialisierung des LCD Boards mit Touch
	int color =0;
	
	RGBQUAD farben;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	RGBQUAD palette [MAX_COLOR_TABLE_SIZE];
	Coordinate corrdinat;
	// Test in Endlosschleife
	
	COMread((char*)&fileHeader,sizeof(fileHeader),1); // bracuht noch einen errohandler 
	COMread((char*)&infoHeader,sizeof(infoHeader),1);
	
	LONG breit = infoHeader.biWidth;
	LONG höhe = infoHeader.biHeight;
	
	
	if(infoHeader.biBitCount == 8){
		COMread((char*)palette,sizeof(RGBQUAD) ,infoHeader.biClrUsed  );

	}
	if(infoHeader.biCompression == BI_RGB){
		DWORD bytesPerLine = (((breit * infoHeader.biBitCount) + 31) / 32) * 4;
			//(((Breite der Zeile)*(Anzahl Bits pro Pixel Eintrag) + 31) / 32) * 4
			for(int y = höhe -1;y >= 0;y--){
				
				for(int x = 0;x < breit ;x++){
					
					if(infoHeader.biBitCount == 8){
					int idx = nextChar();
					color = convertToRgb16(palette[idx]);
					}
					else if(infoHeader.biBitCount == 24){
					COMread((char *)&farben, sizeof(RGBTRIPLE), 1);
						color = convertToRgb16(farben);
					}
					corrdinat.x = x;
					corrdinat.y = y;
					if(x >= 0 && x < MAX_BREITE && y >= 0 && y < MAX_HÖHE){
						
						GUI_drawPoint(corrdinat,color ,DOT_PIXEL_1X1,DOT_FILL_AROUND );
					}
					
				}

				
			}
	}
	while(1) {
		
		
		
		
		
	}
}

// EOF
