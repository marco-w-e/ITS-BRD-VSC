/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    rechner.h
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#ifndef RECHNER_H
#define RECHNER_H
typedef enum {
    IDEL,
    FORWARD,
    BACKWARD,
    ERRO,
}Direction;

extern const char* directionName[];



int getDirection(int oldPhase,int Phase,Direction *currentDirection);
double degree (int menge);

#endif
//EOF
