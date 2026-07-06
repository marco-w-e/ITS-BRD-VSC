/**
 ******************************************************************************
 * @note    Aufgabe 2 - Drehgeber
 * @file    main.c
 * @author  Dylan Dagomber 2815132, Marco Weidner
 * @date    03.05.2026
 * @brief   Hauptprogramm zur Drehgeberauswertung auf dem STM32F4.
 *          Liest zyklisch die Phasensignale des Drehgebers ein, bestimmt
 *          Drehrichtung und Phasenzähler per FSM, berechnet in einem
 *          250 ms / 500 ms Zeitfenster Winkel und Geschwindigkeit und gibt
 *          diese zeichenweise auf dem LCD aus. Fehlerhafte Phasenübergänge
 *          werden per LED signalisiert und per Taster S6 zurückgesetzt.
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
#include "output.h"
#include "rechner.h"
#include "stm32f4xx_hal.h"
#include "timer.h" // Dein Timer-Modul
#include <stdbool.h>
#include <stdio.h>
#include "interrupt.h"


#define TICKS_PER_US 90
#define T250MS (250000 * TICKS_PER_US)
#define T500MS (500000 * TICKS_PER_US)

int main(void) {
  /* Hardware und Peripherie initialisieren */
  initITSboard();
  initTimer();
  GUI_init(DEFAULT_BRIGHTNESS);
  TP_Init(false);
  layout();

  /* Variablen-Initialisierung (Pflicht laut Guide) */
  uint32_t start = TIM2->CNT;
  uint32_t now;
  uint32_t window;
  int phase;
  int oldPhase = gpioAusLesen();
  int amountPhases = 0;
  int oldAmountPhases = 0;
  Direction currentDirection = IDLE;
  double winkel = 0.0;
  double oldWinkel = 0.0;
  double geschwindigkeit = 0.0;

  while (1) {
    
    /* Aktuelle Zeit und Geberzustand erfassen */
    phase = gpioAusLesen();
    now = getTimeStamp();
    window = now - start;
    
    /* Zyklische Berechnung von Winkel und Geschwindigkeit */
     if ((window >= T250MS && phase != oldPhase) || (window >= T500MS)) {
      winkel = degree(amountPhases);
      geschwindigkeit = speed(amountPhases, oldAmountPhases, window);
      degreeToString(winkel);
      speedToString(geschwindigkeit); 
      
      oldWinkel = winkel;
      oldAmountPhases = amountPhases;
      start = now;
    }
    
    /* Auswertung der Drehrichtung bei Flankenwechsel */
    if (phase != oldPhase) {
      getDirection(oldPhase, phase, &currentDirection);

      if (currentDirection == FORWARD) {
        amountPhases++;
        setLED(PIN_LED23); // Vorwärtsanzeige
        clearLED(PIN_LED22);
        clearLED(PIN_LED21);
        setLEDBinary(amountPhases);
      } else if (currentDirection == BACKWARD) {
        amountPhases--;
        setLED(PIN_LED22); // Rückwärtsanzeige
        clearLED(PIN_LED23);
        clearLED(PIN_LED21);
        setLEDBinary(amountPhases);
      }
        else if (currentDirection == ERRO) {
        /* Fehlerbehandlung: Blockieren bis Reset durch S6 */
        setLED(PIN_LED21); // Fehler-LED
        clearLED(PIN_LED23);
        clearLED(PIN_LED22);
        setLEDBinary(amountPhases);
        bool errorActive = true;
        while (errorActive) {
          if (inputS6()) {
            reset(&amountPhases, &oldAmountPhases, &currentDirection, &winkel,
                  &oldWinkel, &geschwindigkeit);
            errorActive = false;
          }
        }
      }
      oldPhase = phase;
    }
    degreePrint(); // LCD-Ausgabe aktualisieren
  }
}