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
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "input.h"
typedef enum {
    IDLE,
    FORWARD,
    BACKWARD,
    ERRO,
}Direction;
char const* directionName[] = {"IDEL","FORWARD","BACKWARD","ERRO"};

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
double degree (int menge){
return menge *(360.0 / 1200.0);

}

