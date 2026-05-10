/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    output.h
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   Schnittstelle zur LED-Steuerung auf dem ITS-Board.
  *          Definiert die Pin-Nummern für LED21–LED23 an GPIOE und
  *          deklariert Funktionen zum Setzen, Löschen und binären
  *          Anzeigen des Phasenzählers auf den LEDs an GPIOD.  
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#ifndef OUTPUT_H
#define OUTPUT_H
//
#define PIN_LED21 5
#define PIN_LED22 6
#define PIN_LED23 7


int clearLED(int led);


int setLED(int led);

int setLEDBinary(int phase);

#endif
//EOF
