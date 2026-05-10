/**
 ******************************************************************************
 * @note    Aufgabe 2 - Drehgeber
 * @file    rechner.c
 * @author  Dylan Dagomber 2815132, Marco Weidner
 * @date    03.05.2026
 * @brief   Berechnung von Winkel und Winkelgeschwindigkeit
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "input.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>

/* Berechnet den aktuellen Winkel basierend auf der Phasenanzahl */
double degree(int menge) { return menge * (360.0 / 1200.0); }

/* Berechnet die Winkelgeschwindigkeit (Grad pro Sekunde) */
double speed(int mengePhasen, int altMengePhasen, uint32_t zeit) {

  double secWindow = (double)zeit / 180000000.0;
  return (double)(mengePhasen - altMengePhasen) * (360.0 / 1200.0) / secWindow;
}
