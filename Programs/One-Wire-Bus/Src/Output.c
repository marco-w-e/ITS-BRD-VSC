#include "stm32f4xx_hal.h"
#include <cstdint>

#define TICKS_PER_US 90
#define T60MICROS (60 * TICKS_PER_US)
#define T480MICORS (480 * TICKS_PER_US)


int pd1High(void){
GPIOD->BSRR=(1 << 1);
return 1;
}
int pd0High(void){
GPIOD->BSRR=(1);
return 1;
}
int pd0Low(void){
GPIOD->BSRR=(1<<16);
return 1;
}
int oneWireSetup(void){
// pd1
GPIOD->MODER &= ~(3U << (2)); 
GPIOD->MODER |=  (1U << (2));
//pd1 push pull mode 
GPIOD->OTYPER &= ~(1U << 1);
pd1High();

GPIOD->MODER &= ~(3U << (1)); 
GPIOD->MODER |=  (1U << (1));
//opendrain
GPIOD->OTYPER |= (1U << 0);

pd0High();
return 1;
}

int impulsDelay(int){




}

// EOF