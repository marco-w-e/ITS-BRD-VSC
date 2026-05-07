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
    PROBLEM // Muss ERROR unbennen weil stm32f4xx.h schon ERROR definiert hat.
} Direction;

int getDirection(int oldPhase,int Phase,Direction *currentDirection);

extern char const* directionName[];

int getDirection(int oldPhase, int Phase, Direction *currentDirection);

#endif
//EOF
