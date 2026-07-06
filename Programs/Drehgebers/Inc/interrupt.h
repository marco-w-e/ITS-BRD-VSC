#ifndef INTERRUPT_H
#define INTERRUPT_H
 
#include "fsm.h"
#include <stdbool.h>
#include <stdint.h>


void initInterrupt(void);

void EXTI1_IRQHandler(void); // Deklaration ISR
void EXTI2_IRQHandler(void); // Deklaration ISR


#endif
// EOF
