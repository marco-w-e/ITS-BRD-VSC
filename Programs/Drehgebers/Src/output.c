/**
 ******************************************************************************
 * @note    Aufgabe 2 - Drehgeber
 * @file    output.c
 * @author  Dylan Dagomber 2815132, Marco Weidner
 * @date    03.05.2026
 * @brief   Steuerung der LED-Ausgänge auf dem ITS-Board.
 ******************************************************************************
 */

#include "output.h"
#include "fehler.h"
#include "stm32f4xx_hal.h"

/* Setzt eine einzelne LED an GPIOE */
int setLED(int led) {
  /* Nutzt das BSRR Register zum atomaren Setzen des Pins */
  GPIOE->BSRR = (1 << led);
  return WORKING;
}

/* Löscht eine einzelne LED an GPIOE*/
int clearLED(int led) {
  /* Offset von 16 im BSRR löscht den entsprechenden Pin */
  GPIOE->BSRR = (1 << (led + 16));
  return WORKING;
}

/* Zeigt den Phasenzähler binär an GPIOD an */
int setLEDBinary(int phase) {
  /* Begrenzung auf 8 Bit (0-255) */
  int bits = phase & 0xFF;

  /* Zuerst alle 8 LEDs löschen */
  GPIOD->BSRR = (0xFF << 16);
  
  /* Neue Bitmaske setzen */
  GPIOD->BSRR = bits;
  
  return WORKING;
}