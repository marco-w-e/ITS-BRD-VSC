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
int spLength;
int spIndex = 1;
bool spHasNext= false;

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
  }else if(spHasNext){
    if (spIndex == 1) {
              lcdGotoXY(1, 4); 
          }
      lcdPrintC(speedBufffer[spIndex]);
      spIndex++;
      if(spIndex >= spLength){
        spHasNext = false ;

    }
  }
}
void degreeToString(double degree){
  sprintf (degreeBufffer, " %.3f",degree);
  deLength = strlen(degreeBufffer);
  deIndex = 1;
  deHasNext = true;

}
void speedToString(double speed){
  sprintf (speedBufffer, " %.3f",speed);
  spLength = strlen(speedBufffer);
  spIndex = 1;
  spHasNext = true;

}
