/**
  ******************************************************************************
  * @note    Aufgabe 2 - Drehgeber
  * @file    main.c
  * @author  Dylan Dagomber 2815132, Marco Weidner
  * @date    03.05.2026
  * @brief   
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "init.h"
#include "input.h"
#include "rechner.h"
#include "timer.h" // Dein Timer-Modul
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "display_output.h"
// HOFFE DAS IST RICHTIG IDK hab chat wegen dem timer gefragt un der meinte das das stimmt.
//war zu doof zum selber rechnen mäh :/
#define T250MS 45000000  // 180MHz * 0.25s
#define T500MS 90000000  // 180MHz * 0.50s

/// LIES DIE KOMMENTARA HAB MIR MÜHE GEGEBEN !!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int main(void) {
    initITSboard(); 
    initTimer();        
    GUI_init(DEFAULT_BRIGHTNESS);
	TP_Init(false);
	layout();
	 uint32_t start = TIM2->CNT;
	 uint32_t now;
	 uint32_t window;
   
	 int phase; // phase gerade hoffentlich
    int oldPhase = gpioAusLesen(); // sagt der name ig
	
	int amountPhases = 0; 
	int oldAmountPhases=0;			// ich denke ist schlüssig oder?
       // die zeit an der der timer startet bin mir nicht sicher ob das das richtige ist work in progress ahha
    Direction currentDirection;        //....
    double winkel = 0.0;	
	double oldWinkel = 0.0;			//du weißt
    double geschwindigkeit = 0.0;		// ^

    while(1) {
        // die kommentare sind noch nicht fertige  methoden überwiegend
        phase = gpioAusLesen();
        
        if (phase != oldPhase) {
            getDirection(oldPhase, phase, &currentDirection);
            if (currentDirection == FORWARD) {
                amountPhases++;
                // LED D23 an
            } else if (currentDirection == BACKWARD) {
                amountPhases--;
                // LED D22 an
            } else if (currentDirection == ERRO) {
                // LED D21 an und erro loop bis input s6 genommen wirdd
            }
            oldPhase = phase;
            
		}
       now = TIM2->CNT;
	   window = now - start;
		if((window >= T250MS && phase!=oldPhase )|| (window >= T500MS)){

			winkel = degree(amountPhases);
			geschwindigkeit = speed(amountPhases,oldAmountPhases,window);
			
			if(winkel != oldWinkel){
			degreePrint(winkel);
			speedPrint(geschwindigkeit);
			}
			if(oldAmountPhases != amountPhases){
				speedPrint(geschwindigkeit);
			}
			oldWinkel= winkel;
			oldAmountPhases = amountPhases;
			// viel von den  sachen müssen noch in unterfunktionen und diese in ihre passende module
			// dasselbe für den winkel speed dann nur noch led aus gabe und 
			// erro loop :)
		}
       
		

    }
}