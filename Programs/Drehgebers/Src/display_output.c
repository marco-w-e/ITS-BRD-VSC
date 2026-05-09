/**
 ******************************************************************************
 * @note    Aufgabe 2 - Drehgeber
 * @file    display_output.c
 * @author  Dylan Dagomber 2815132, Marco Weidner
 * @date    03.05.2026
 * @brief
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lcd.h"
char speedBufffer[32];

char degreeBufffer[32];
int deLength;
int deIndex = 1;
bool deHasNext= false;

void layout(void){
    lcdGotoXY(1, 1);
    lcdPrintS("Winkel:");
	  lcdGotoXY(1, 3);
    lcdPrintS("Speed:");
}

int degreePrint(void){
  if(deHasNext){
   if (deIndex == 1) {
            lcdGotoXY(1, 2); 
        }
    lcdPrintC(degreeBufffer[deIndex]);
    deIndex++;
    if(deIndex >= deLength){
      deHasNext = false ;

    }
  }
}

int degreePrint1(double degree){
  snprintf (degreeBufffer,sizeof degreeBufffer, " %.3f deg",degree);
	lcdGotoXY(1, 2);
  lcdPrintC(degreeBufffer[1]);
  
}
int speedPrint(double speed){
    snprintf(speedBufffer,sizeof speedBufffer, " %.3f d/sek",speed);
		lcdGotoXY(1, 4);
    lcdPrintC(speedBufffer[1]);
}

void degreeToString(double degree){
  snprintf (degreeBufffer,sizeof degreeBufffer, " %.3f",degree);
  deLength = (int)strlen(degreeBufffer);
  deIndex =1;
  deHasNext= true;

}
