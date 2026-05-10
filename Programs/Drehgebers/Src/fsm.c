/**
 ******************************************************************************
 * @note    Aufgabe 2 - Drehgeber
 * @file    fsm.c
 * @author  Dylan Dagomber 2815132, Marco Weidner
 * @date    03.05.2026
 * @brief   Finite State Machine (FSM) für die Drehgeberauswertung.
 *          Ermittelt anhand einer Zustandsmatrix die aktuelle Drehrichtung
 *          (FORWARD, BACKWARD, IDLE, ERRO) aus aufeinanderfolgenden
 * Phasenzuständen und stellt eine Reset-Funktion bereit, die alle
 * Zustandsvariablen (Phasenanzahl, Richtung, Winkel, Geschwindigkeit)
 * initialisiert.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "fsm.h"
#include "fehler.h"
#include "input.h"
#include "rechner.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>


static const Direction matrix[4][4] = {{IDLE, BACKWARD, FORWARD, ERRO},
                                       {FORWARD, IDLE, ERRO, BACKWARD},
                                       {BACKWARD, ERRO, IDLE, FORWARD},
                                       {ERRO, FORWARD, BACKWARD, IDLE}};

                                       /* Bestimmt die Richtung basierend auf dem Phasenübergang */
int getDirection(int oldPhase, int Phase, Direction *currentDirection) {

  *currentDirection = matrix[oldPhase][Phase];
  return WORKING;
}

/* Setzt alle Zähler und berechneten Werte auf den Initialzustand zurück */
int reset(int *amountPhases, int *oldAmountPhases, Direction *currentDirection,
          double *winkel, double *oldWinkel, double *geschwindigkeit) {
  *amountPhases = 0;
  *oldAmountPhases = 0;
  *currentDirection = IDLE;
  *winkel = 0.0;
  *oldWinkel = 0.0;
  *geschwindigkeit = 0.0;
  return WORKING;
}