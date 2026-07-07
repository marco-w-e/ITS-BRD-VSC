/**
 ******************************************************************************
 * @note    Aufgabe 2 - Drehgeber
 * @file    input.c
 * @author  Dylan Dagomber 2815132, Marco Weidner
 * @date    03.05.2026
 * @brief   Einlesen der GPIO-Eingänge für den Drehgeber und den Taster S6.
 *          Liest die zwei Phasensignale des Drehgebers (Bits 0–1 von GPIOF)
 *          sowie den aktiven-low Taster S6 (Bit 6 von GPIOF) aus.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "error.h"
#include "stm32f4xx.h"
#include <stdbool.h>

#include "fehler.h"
#include "lcd.h"

int gpioAusLesen() { return GPIOG->IDR & (0x03U); }

bool inputS6(void) { return !(GPIOG->IDR & (1 << 6)); }