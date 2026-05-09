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