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
typedef enum {
    IDLE,
    FORWARD,
    BACKWARD,
    PROBLEM // Muss ERROR unbennen weil stm32f4xx.h schon ERROR definiert hat.,
}Direction;

char const* directionName[] = {"IDLE","FORWARD","BACKWARD","PROBLEM"};

static const Direction  matrix[4][4] = {
{IDLE,BACKWARD,FORWARD,PROBLEM},
{FORWARD,IDLE,PROBLEM,BACKWARD},
{BACKWARD,PROBLEM,IDLE,FORWARD},
{PROBLEM,FORWARD,BACKWARD,IDLE}
};

int getDirection(int oldPhase,int Phase,Direction *currentDirection){
    
  *currentDirection = matrix[oldPhase][Phase];
  return WORKING;
}