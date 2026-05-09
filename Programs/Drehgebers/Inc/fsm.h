/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    fsm.h
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#ifndef FSM_H
#define FSM_H
//
typedef enum {
    IDLE,
    FORWARD,
    BACKWARD,
    ERRO,
}Direction;

int getDirection(int oldPhase,int Phase,Direction *currentDirection);


int reset(int *amountPhases, int *oldAmountPhases, Direction *currentDirection,
           double *winkel, double *oldWinkel, double *geschwindigkeit);
#endif
//EOF
