/**
 ******************************************************************************
 * @note    Aufgabe 5 - Drehgeber per Interrupt
 * @file    main.c
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
#include "interrupt.h"
#include "lcd.h"
#include "output.h"
#include "rechner.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
#include <stdbool.h>
#include <stdio.h>


#define TICKS_PER_US 90
#define T250MS (250000 * TICKS_PER_US)
#define T500MS (500000 * TICKS_PER_US)

// Zugriff auf die externen volatilen Variablen aus interrupt.c für Reset
extern volatile int amountPhases;
extern volatile Direction direction;
extern volatile uint32_t lastPhaseChangeTime ;
extern volatile int now;

int main(void) {
  /* Hardware und Peripherie initialisieren */
  initITSboard();
  initTimer();
  GUI_init(DEFAULT_BRIGHTNESS);
  TP_Init(false);
  layout();
  initInterrupt();

  /* Variablen für die zyklische LCD-Berechnung */
  uint32_t startTime = getTimeStamp();
  uint32_t lastDisplayTimestamp = startTime;

  int lastProcessedPhases = 0;
  int oldAmountPhases = 0;
  double winkel = 0.0;
  double oldWinkel = 0.0;
  double geschwindigkeit = 0.0;

  while (1) {
    int currentPhaseCount;
    uint32_t currentPhaseTime;

    // 1. Sicheres und konsistentes Auslesen aus den ISR-Variablen
    readEncoderData(&currentPhaseCount, &currentPhaseTime);
    Direction currentDirCopy = direction;

    uint32_t currentTime = getTimeStamp();

    /* Zyklische LCD-Ausgabe alle 250ms (bei Änderung) oder spätestens nach
     * 500ms */
    if (((currentTime - lastDisplayTimestamp) >= T250MS &&
         currentPhaseCount != oldAmountPhases) ||
        ((currentTime - lastDisplayTimestamp) >= T500MS)) {

      winkel = degree(currentPhaseCount);

      // Berechnung basierend auf der Zeitdifferenz der tatsächlichen
      // ISR-Flanken
      uint32_t timeDifference = now - lastDisplayTimestamp;

      // Absicherung falls im Zeitfenster kein neuer Interrupt kam (timeDifference
      // == 0)
      if (currentPhaseCount == oldAmountPhases || timeDifference == 0) {
        geschwindigkeit = 0.0;
      } else {
        geschwindigkeit =
            speed(currentPhaseCount, oldAmountPhases, timeDifference);
      }

      degreeToString(winkel);
      speedToString(geschwindigkeit);

      oldWinkel = winkel;
      oldAmountPhases = currentPhaseCount;
      lastDisplayTimestamp = currentTime; // Auffrischen für den Display-Zyklus
    }

    /* 2. LED-Visu & Fehlerbehandlung */
   

      if (currentDirCopy == FORWARD) {
        setLED(PIN_LED23);
        clearLED(PIN_LED22);
        clearLED(PIN_LED21);
        setLEDBinary(currentPhaseCount);
      } else if (currentDirCopy == BACKWARD) {
        setLED(PIN_LED22);
        clearLED(PIN_LED23);
        clearLED(PIN_LED21);
        setLEDBinary(currentPhaseCount);
      } else if (currentDirCopy == ERRO) {
        setLED(PIN_LED21);
        clearLED(PIN_LED23);
        clearLED(PIN_LED22);
        setLEDBinary(currentPhaseCount);

        bool hasError = true;
        while (hasError) {
          if (inputS6()) {
            // Reset übergeben (Casting der globalen ISR-Variablen)
            reset((int *)&amountPhases, &oldAmountPhases,
                  (Direction *)&direction, &winkel, &oldWinkel,
                  &geschwindigkeit);

            // Auch den Interrupt-Zeitstempel zurücksetzen
            lastPhaseChangeTime  = getTimeStamp();
            currentPhaseCount = 0;
            hasError = false;
          }
        }
      }
      lastProcessedPhases = currentPhaseCount;
    

    degreePrint();
  }
}  