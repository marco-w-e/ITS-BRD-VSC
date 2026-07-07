#ifndef INTERRUPT_H
#define INTERRUPT_H
 
#include "fsm.h"
#include <stdbool.h>
#include <stdint.h>

extern volatile int amountPhases;
extern volatile Direction currentDirection;
extern volatile int phase;
extern volatile int oldPhase;
extern volatile int now;
extern volatile int oldTime;
extern volatile int window;

void initInterrupt(void);

void EXTI1_IRQHandler(void); // Deklaration ISR
void EXTI2_IRQHandler(void); // Deklaration ISR
int getPhase(void);

#endif
// EOF
