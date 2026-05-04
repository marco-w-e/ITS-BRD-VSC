<<<<<<< HEAD

#include "error.h"
#include "stm32f4xx.h"
#include <stdbool.h>
#include "lcd.h"


int gpioAusLesen(){

    return GPIOF->IDR & (0x03U);

}
=======
/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    input.c
  * @author  Dylan Dagomber 2815132, Marco Weidner 
  * @date    03.05.2026
  * @brief   
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
>>>>>>> 8cc0e88576f887105e11da1653c85052b1a58dfc
