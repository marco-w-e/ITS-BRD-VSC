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
#include "lcd.h"
char displayBufffer[32];

void layout(void){
    lcdGotoXY(1, 1);
    lcdPrintS("Winkel:");
	  lcdGotoXY(1, 3);
    lcdPrintS("Speed:");
}
int degreePrint(double degree){
  snprintf (displayBufffer,sizeof displayBufffer, " %.3f deg",degree);
	lcdGotoXY(1, 2);
  lcdPrintC(displayBufffer[1]);
  lcdPrintC(displayBufffer[2]);
}
int speedPrint(double speed){
    snprintf(displayBufffer,sizeof displayBufffer, " %.3f d/sek",speed);
		lcdGotoXY(1, 4);
    lcdPrintC(displayBufffer[1]);
}
