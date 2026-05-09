/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    fsm.c
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "input.h"
#include "rechner.h"
#include "fsm.h"
#include "fehler.h"

static const Direction matrix[4][4] = {
    {IDLE,     BACKWARD, FORWARD,  ERRO},
    {FORWARD,  IDLE,     ERRO,     BACKWARD},
    {BACKWARD, ERRO,     IDLE,     FORWARD},
    {ERRO,     FORWARD,  BACKWARD, IDLE}
};

int getDirection(int oldPhase,int Phase,Direction *currentDirection){
    
  *currentDirection = matrix[oldPhase][Phase];
  return 1;
}

void reset(int *amountPhases, int *oldAmountPhases, 
           Direction *currentDirection, double *winkel, 
           double *oldWinkel, double *geschwindigkeit)
{
    *amountPhases    = 0;
    *oldAmountPhases = 0;
    *currentDirection = IDEL;
    *winkel          = 0.0;
    *oldWinkel       = 0.0;
    *geschwindigkeit = 0.0;
}