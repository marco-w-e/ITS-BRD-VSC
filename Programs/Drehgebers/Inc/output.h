/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    output.h
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   
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


void clearLED(int led);


void setLED(int led);

void setLEDBinary(int phase);

#endif
//EOF
