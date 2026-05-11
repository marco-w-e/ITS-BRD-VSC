/**
 ******************************************************************************
 * @note    Aufgabe 2 - Drehgeber
 * @file    rechner.h
 * @author  Dylan Dagomber 2815132, Marco Weidner
 * @date    03.05.2026
 * @brief   Berechnung von Winkel und Winkelgeschwindigkeit
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stdint.h"   
#ifndef RECHNER_H
#define RECHNER_H

int calculateDrehgeschwindigkeit(int oldPhase, int newPhase, int timeInterval);

double degree(int menge);

double speed(int mengePhasen, int altMengePhasen, uint32_t zeit);
#endif
// EOF
