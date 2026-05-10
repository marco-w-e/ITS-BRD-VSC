/**
 ******************************************************************************
 * @note    Aufgabe 2 - Drehgeber
 * @file    display_output.h
 * @author  Dylan Dagomber 2815132, Marco Weidner
 * @date    03.05.2026
 * @brief   Schnittstelle zur LCD-Ausgabe von Winkel und Geschwindigkeit.
 *          Deklariert Funktionen für das Display-Layout sowie die
 *          zeichenweise, nicht-blockierende Ausgabe von Grad- und
 *          Geschwindigkeitswerten als formatierte Strings.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#ifndef DISPLAY_OUTPUT_H
#define DISPLAY_OUTPUT_H
//
char displayBuffer[32];
void layout(void);
int degreePrint(void);
void degreeToString(double winkel);
int speedPrint(double speed);
void speedToString(double speed);

int phasePrint(int phase);
#endif
// EOF
