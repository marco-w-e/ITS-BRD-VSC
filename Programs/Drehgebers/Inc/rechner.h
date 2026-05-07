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
#ifndef RECHNER_H
#define RECHNER_H
//
int calculateDrehwinkel(int phase);

int calculateDrehgeschwindigkeit(int oldPhase, int newPhase, int timeInterval);

#endif
//EOF
