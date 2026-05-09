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

#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "additionalFonts.h"
#include "display_output.h"
#include "fontsFLASH.h"
#include "fsm.h"
#include "init.h"
#include "input.h"
#include "lcd.h"
#include "rechner.h"
#include "stm32f4xx_hal.h"
#include "timer.h" // Dein Timer-Modul
#include <stdbool.h>
#include <stdio.h>
#include "output.h"

// HOFFE DAS IST RICHTIG IDK hab chat wegen dem timer gefragt un der meinte das
// das stimmt.
// war zu doof zum selber rechnen mäh :/
#define T250MS 45000000 // 180MHz * 0.25s
#define T500MS 90000000 // 180MHz * 0.50s

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

  int phase;                     // phase gerade hoffentlich
  int oldPhase = gpioAusLesen(); // sagt der name ig

<<<<<<< HEAD
  int amountPhases = 0;
  int oldAmountPhases = 0; // ich denke ist schlüssig oder?
  // die zeit an der der timer startet bin mir nicht sicher ob das das richtige
  // ist work in progress ahha
  Direction currentDirection; //....
  double winkel = 0.0;
  double oldWinkel = 0.0;       // du weißt
  double geschwindigkeit = 0.0; // ^
=======
			winkel = degree(amountPhases);
			geschwindigkeit = speed(amountPhases,oldAmountPhases,window);
			degreeToString(winkel);
			
            if((winkel != oldWinkel) && (window >= T500MS)){
                degreePrint();
			
			}
			if(oldAmountPhases != amountPhases && (window >= T500MS)){
				speedPrint(geschwindigkeit);
			}
			oldWinkel= winkel;
			oldAmountPhases = amountPhases;
			// viel von den  sachen müssen noch in unterfunktionen und diese in ihre passende module
			// dasselbe für den winkel speed dann nur noch led aus gabe und 
			// erro loop :)
		}
       
		
>>>>>>> 34fba3e15c5fa62f2e74299464d021af97a2a164

  while (1) {
    // die kommentare sind noch nicht fertige  methoden überwiegend
    phase = gpioAusLesen();

    if (phase != oldPhase) {
      getDirection(oldPhase, phase, &currentDirection);
      if (currentDirection == FORWARD) {
        amountPhases++;
        setLED(PIN_LED23);
        clearLED(PIN_LED22);
        setLEDBinary(amountPhases);
    
      } else if (currentDirection == BACKWARD) {
        amountPhases--;
        setLED(PIN_LED22);
        clearLED(PIN_LED23);
        setLEDBinary(amountPhases);

    } else if (currentDirection == ERRO) {
        setLED(PIN_LED21);
        clearLED(PIN_LED23);
        clearLED(PIN_LED22);
        setLEDBinary(amountPhases);
      }
      oldPhase = phase;
    }


    now = TIM2->CNT;
    window = now - start;
    if ((window >= T250MS && phase != oldPhase) || (window >= T500MS)) {

      winkel = degree(amountPhases);
      geschwindigkeit = speed(amountPhases, oldAmountPhases, window);

      if (winkel != oldWinkel) {
        degreePrint(winkel);
        speedPrint(geschwindigkeit);
      }
      if (oldAmountPhases != amountPhases) {
        speedPrint(geschwindigkeit);
      }
      oldWinkel = winkel;
      oldAmountPhases = amountPhases;
      // viel von den  sachen müssen noch in unterfunktionen und diese in ihre
      // passende module dasselbe für den winkel speed dann nur noch led aus
      // gabe und erro loop :)
    }
  }
}