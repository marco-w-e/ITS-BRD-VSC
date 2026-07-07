/**
 ******************************************************************************
 * @note    Aufgabe 5 - Drehgeber per Interrupt
 * @file    interrupt.c
 * @author  Dylan Dagomber 2815132, Marco Weidner
 * @date    06.07.2026
 * @brief   
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
#include "timer.h" // Dein Timer-Modul

extern volatile int amountPhases = 0;
extern volatile Direction currentDirection = IDLE;
extern volatile int phase = 0;
extern volatile int oldPhase = 0;
extern volatile int now = 0;
extern volatile int oldTime =0;
extern volatile int window;

/* Configure EXTI2 (Pin PG2) for encoder interrupt */
void initInterrupt(void)
{
	/* Enable clocks */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; /* Clock for GPIO Port G */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; /* System configuration clock enable */

	GPIOG->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1);
    
	SYSCFG->EXTICR[0] &= ~(0x0f << (4*0)); /* Remove old selection */
	SYSCFG->EXTICR[0] |= 0x06 << (4*0);   /* 0x06 : Select port G */

	/* Routing Pin 1 of Port G -> EXTI2 */
	SYSCFG->EXTICR[0] &= ~(0x0f << (4*1)); /* Remove old selection */
	SYSCFG->EXTICR[0] |= 0x06 << (4*1);   /* 0x06 : Select port G */


	/* Trigger and mask */
	/* EXTI->RTSR |= (1<<2); */ /* select rising trigger for INT2 if needed */
	EXTI->RTSR |= (1 << 0) | (1 << 1); /* Rising Trigger für EXTI0 & EXTI1 */
    EXTI->FTSR |= (1 << 0) | (1 << 1); /* Falling Trigger für EXTI0 & EXTI1 */
    EXTI->IMR  |= (1 << 0) | (1 << 1); /* Interrupt-Maske öffnen für beide */

    NVIC_SetPriority(EXTI0_IRQn, 1); /* Setup EXTI2 priority */
	NVIC_EnableIRQ(EXTI0_IRQn); /* Enable EXTI2 */
    
	NVIC_SetPriority(EXTI1_IRQn, 1); /* Setup EXTI2 priority */
	NVIC_EnableIRQ(EXTI1_IRQn); /* Enable EXTI2 */
}

// ISR für EXTI1 (Pin G1 / Spur A)
void EXTI1_IRQHandler(void) {
    if (EXTI->PR & (1 << 1)) { // Prüfen, ob EXTI1 ausgelöst hat
        EXTI->PR = (1 << 1);   // Pending-Bit löschen!
        uint32_t now = getTimeStamp();
		window = now - oldTime;
		oldTime = now;
        phase = gpioAusLesen();    // Aktuellen Zustand (Spur A und B) einlesen
        if (phase != oldPhase) {
            getDirection(oldPhase, phase, (Direction*)&currentDirection);
            if (currentDirection == FORWARD)  amountPhases++;
            if (currentDirection == BACKWARD) amountPhases--;
            
        }
    }
}

// ISR für EXTI2 (Pin G2 / Spur B)
void EXTI2_IRQHandler(void) {
    if (EXTI->PR & (1 << 2)) { // Prüfen, ob EXTI2 ausgelöst hat
        EXTI->PR = (1 << 2);   // Pending-Bit löschen!
        uint32_t now = getTimeStamp();
		window = now - oldTime;
		oldTime = now;
        phase = gpioAusLesen();
        if (phase != oldPhase) {
            getDirection(oldPhase, phase, (Direction*)&currentDirection);
            if (currentDirection == FORWARD)  amountPhases++;
            if (currentDirection == BACKWARD) amountPhases--;
            
        }
    }
}
int getPhase(void){
	return phase;
}