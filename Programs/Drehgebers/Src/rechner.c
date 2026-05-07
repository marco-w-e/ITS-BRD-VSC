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

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "input.h"
typedef enum {
    IDEL,
    FORWARD,
    BACKWARD,
    PROBLEM // Muss ERROR unbennen weil stm32f4xx.h schon ERROR definiert hat.,
}Direction;
char const* directionName[] = {"IDEL","FORWARD","BACKWARD","PROBLEM"};

static const Direction  matrix[4][4] = {
{IDEL,BACKWARD,FORWARD,PROBLEM},
{FORWARD,IDEL,PROBLEM,BACKWARD},
{BACKWARD,PROBLEM,IDEL,FORWARD},
{PROBLEM,FORWARD,BACKWARD,IDEL}
};

int getDirection(int oldPhase,int Phase,Direction *currentDirection){
    
  *currentDirection = matrix[oldPhase][Phase];
  return 1;
}
