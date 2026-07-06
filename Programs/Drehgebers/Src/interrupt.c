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

volatile uint32_t phasenCount = 0;
volatile uint32_t lastTime = 0;
/* Configure EXTI2 (Pin PG2) for encoder interrupt */
void initInterrupt(void)
{
	/* Enable clocks */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; /* Clock for GPIO Port G */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; /* System configuration clock enable */



    SYSCFG->EXTICR[0] &= ~(0x0f << (4*1)); /* Remove old selection */
	SYSCFG->EXTICR[0] |= 0x06 << (4*1);   /* 0x06 : Select port G */

	/* Routing Pin 2 of Port G -> EXTI2 */
	SYSCFG->EXTICR[0] &= ~(0x0f << (4*2)); /* Remove old selection */
	SYSCFG->EXTICR[0] |= 0x06 << (4*2);   /* 0x06 : Select port G */


	/* Trigger and mask */
	/* EXTI->RTSR |= (1<<2); */ /* select rising trigger for INT2 if needed */
	EXTI->RTSR |= (1<<1); //select rising trigger for INT1
    EXTI->FTSR |= (1<<1); //select falling trigger for INT1
    
    EXTI->IMR |= (1<<1);   /* Unmask INT1 */
    
    EXTI->RTSR |= (1<<2); //select rising trigger for INT2
    EXTI->FTSR |= (1<<2); //select falling trigger for INT2
  
	EXTI->IMR |= (1<<2);   /* Unmask INT2 */

    NVIC_SetPriority(EXTI1_IRQn, 1); /* Setup EXTI2 priority */
	NVIC_EnableIRQ(EXTI1_IRQn); /* Enable EXTI2 */
    
	NVIC_SetPriority(EXTI2_IRQn, 1); /* Setup EXTI2 priority */
	NVIC_EnableIRQ(EXTI2_IRQn); /* Enable EXTI2 */
}

void EXTI1_IRQHandler(void){
 uint32_t now = getTimeStamp();
uint32_t phase = gpioAusLesen();
 EXTI -> PR = (1 << 2);

    
}