/**
 ******************************************************************************
 * @note    Aufgabe 5 - Drehgeber per Interrupt
 * @file    interrupt.c
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "interrupt.h"
#include "fehler.h"
#include "fsm.h"
#include "input.h"
#include "output.h"
#include "stm32f4xx.h"
#include <stdint.h>
#include "timer.h"

// Definition der globalen Variablen
volatile int amountPhases = 0;
volatile Direction currentDirection = IDLE;
volatile int phase = 0;
volatile int oldPhase = 0;

// NEU: Zeitstempel des letzten gültigen Phasenwechsels
volatile uint32_t timestampPhases = 0;

void initInterrupt(void)
{
    /* Enable clocks */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;  /* Clock for GPIO Port G */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; /* System configuration clock enable */

    /* Pins PG0 und PG1 als Input definieren */
    GPIOG->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1);
    
    /* Routing für Pin 0 von Port G -> EXTI0 */
    SYSCFG->EXTICR[0] &= ~(0x0f << (4*0)); 
    SYSCFG->EXTICR[0] |= 0x06 << (4*0);   

    /* Routing für Pin 1 von Port G -> EXTI1 */
    SYSCFG->EXTICR[0] &= ~(0x0f << (4*1)); 
    SYSCFG->EXTICR[0] |= 0x06 << (4*1);   

    /* Trigger (Any Edge) und Maskierung für EXTI0 und EXTI1 */
    EXTI->RTSR |= (1 << 0) | (1 << 1); /* Rising Trigger */
    EXTI->FTSR |= (1 << 0) | (1 << 1); /* Falling Trigger */
    EXTI->IMR  |= (1 << 0) | (1 << 1); /* Unmask */

    /* NVIC aktivieren */
    NVIC_SetPriority(EXTI0_IRQn, 1); 
    NVIC_EnableIRQ(EXTI0_IRQn); 
    
    NVIC_SetPriority(EXTI1_IRQn, 1); 
    NVIC_EnableIRQ(EXTI1_IRQn); 
    
    // Startphase einmalig einlesen
    oldPhase = gpioAusLesen();
    timestampPhases = getTimeStamp();
}

// ISR für EXTI0 (Pin G0 / Spur A)
void EXTI0_IRQHandler(void) {
    // 1. Zeitstempel SOFORT holen (Vorgabe PDF)
    uint32_t t_capture = getTimeStamp();

    if (EXTI->PR & (1 << 0)) { 
        EXTI->PR = (1 << 0);   
        
        phase = gpioAusLesen();    
        if (phase != oldPhase) {
            getDirection(oldPhase, phase, (Direction*)&currentDirection);
            if (currentDirection == FORWARD)  amountPhases++;
            if (currentDirection == BACKWARD) amountPhases--;
            
            // Nur bei echtem Wechsel den globalen Zeitstempel aktualisieren
            timestampPhases = t_capture;
            oldPhase = phase; 
        }
    }
}

// ISR für EXTI1 (Pin G1 / Spur B)
void EXTI1_IRQHandler(void) {
    // 1. Zeitstempel SOFORT holen (Vorgabe PDF)
    uint32_t t_capture = getTimeStamp();

    if (EXTI->PR & (1 << 1)) { 
        EXTI->PR = (1 << 1);   
        
        phase = gpioAusLesen();
        if (phase != oldPhase) {
            getDirection(oldPhase, phase, (Direction*)&currentDirection);
            if (currentDirection == FORWARD)  amountPhases++;
            if (currentDirection == BACKWARD) amountPhases--;
            
            // Nur bei echtem Wechsel den globalen Zeitstempel aktualisieren
            timestampPhases = t_capture;
            oldPhase = phase; 
        }
    }
}

/**
 * 
 * Verhindert Race Conditions, falls mitten im Lesevorgang ein Interrupt auftritt.
 */
void getEncoderDataSafe(int *outPhases, uint32_t *outTimestamp) {
    int t_phases1, t_phases2;
    uint32_t t_time1, t_time2;

    do {
        t_time1   = timestampPhases;
        t_phases1 = amountPhases;

        t_time2   = timestampPhases;
        t_phases2 = amountPhases;
    } while ((t_time1 != t_time2) || (t_phases1 != t_phases2));

    *outPhases = t_phases1;
    *outTimestamp = t_time1;
}

int getPhase(void){
    return phase;
}