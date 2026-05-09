/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    rechner.c
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   Berechnung von Winkel und Winkelgeschwindigkeit
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "input.h"



double degree (int menge){
return menge *(360.0 / 1200.0);

}

double speed (int mengePhasen,int altMengePhasen,uint32_t zeit){
 
  double secWindow = (double)zeit / 180000000.0;
       return (double)(mengePhasen - altMengePhasen) * (360.0 / 1200.0) / secWindow;
    
}
