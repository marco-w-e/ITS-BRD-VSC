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

void setLED(int led){

  GPIOE -> BSRR = (1<<led);
}

void clearLED(int led){

  GPIOE -> BSRR = (1<< (led + 16));
}

void setLEDBinary(int phase){

  int bits = phase & 0xFF;

  GPIOD->BSRR = (0xFF << 16);
  GPIOD->BSRR = bits;

}