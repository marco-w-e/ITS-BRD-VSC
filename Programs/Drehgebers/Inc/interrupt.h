#ifndef INTERRUPT_H
#define INTERRUPT_H
 
#include "fsm.h"
#include <stdbool.h>
#include <stdint.h>

// Deklarationen der Variablen für andere Module (ohne Werte-Zuweisung!)
extern volatile int amountPhases;
extern volatile Direction currentDirection;
extern volatile int phase;
extern volatile int oldPhase;
extern volatile int now;
extern volatile int oldTime;
extern volatile int window;

void initInterrupt(void);

void EXTI0_IRQHandler(void); // Passend zu Pin 0
void EXTI1_IRQHandler(void); // Passend zu Pin 1
int getPhase(void);
void getEncoderDataSafe(int *outPhases, uint32_t *outTimestamp);

#endif