/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    output.c
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "output.h"
#include "stm32f4xx_hal.h"
#include "fehler.h"

int setLED(int led){

  GPIOE -> BSRR = (1<<led);
  return WORKING;
}

int clearLED(int led){

  GPIOE -> BSRR = (1<< (led + 16));
  return WORKING;
}

int setLEDBinary(int phase){

  int bits = phase & 0xFF;

  GPIOD->BSRR = (0xFF << 16);
  GPIOD->BSRR = bits;
  return WORKING;

}