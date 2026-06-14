#include "stm32f4xx_hal.h"
#include "timer.h"
#include "fehler.h"
#include "output.h"
#include <stdint.h>




int pd1High(void){
GPIOD->BSRR=(1 << 1);
return WORKING;
}
int pd0High(void){
GPIOD->BSRR=(1); // digga wir haben da eine 0 anstatt einer 1 gehabt cooked warum bin ich so blind wie kann mir das nicht auf fallen
return WORKING;  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
int pd0Low(void){
GPIOD->BSRR=(1<<16);
return WORKING;
}
int oneWireSetup(void){
// pd1
GPIOD->MODER &= ~(3U << (2)); 
GPIOD->MODER |=  (1U << (2));
//pd1 push pull mode 
GPIOD->OTYPER &= ~(1U << 1);
pd1High();
//pd0
GPIOD->MODER &= ~(3U << (0)); 
GPIOD->MODER |=  (1U << (0));
//opendrain
GPIOD->OTYPER |= (1U << 0);

pd0High();
return WORKING;
}

int impulsDelay(uint32_t Microsek){
TIM2 -> CNT = 0;
TIM2 -> CR1 |= 1U;
while(TIM2 -> CNT < Microsek){
}

TIM2 -> CR1 &= ~1U;
return WORKING;
}



 
// EOF