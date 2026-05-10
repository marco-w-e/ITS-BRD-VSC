/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    input.h
  * @author  Dylan Dagomber 2815132, Marco Weidner 
  * @date    03.05.2026
  * @brief   Schnittstelle zum Einlesen der Drehgeber- und Tastereingänge.
  *          Deklariert Funktionen zum Auslesen der zwei Phasensignale
  *          an GPIOF (Bits 0–1) sowie des aktiven-low Tasters S6 (Bit 6).
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#ifndef INPUT_H
#define INPUT_H
//
int gpioAusLesen();
bool inputS6(void);
#endif
//EOF
