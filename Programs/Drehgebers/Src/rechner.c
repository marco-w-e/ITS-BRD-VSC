<<<<<<< HEAD
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "input.h"
typedef enum {
    IDEL,
    FORWARD,
    BACKWARD,
    ERRO,
}Direction;

static const Direction  matrix[4][4]{
{IDEL,BACKWARD,FORWARD,ERRO}
{FORWARD,IDLE,ERRO,BACKWARD}
{BACKWARD,ERRO,IDLE,FORWARD}
{ERRO,FORWARD,BACKWARD,IDLE}
}

getDirection(oldPhase,Phase){
    
}
=======
/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    rechner.c
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
>>>>>>> 8cc0e88576f887105e11da1653c85052b1a58dfc
