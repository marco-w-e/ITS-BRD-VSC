/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    display_output.h
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#ifndef DISPLAY_OUTPUT_H
#define DISPLAY_OUTPUT_H
//
char displayBuffer[32];
void layout(void);
int degreePrint(void);
int degreePrint1(double winkel);
void degreeToString(double winkel );
int  speedPrint(double speed);

int  phasePrint(int phase);
#endif
//EOF
