#include "stm32f4xx_hal.h"
#include "timer.h"
#include <stdint.h>

#define TICKS_PER_US 90
#define T60MICROS (60 * TICKS_PER_US)
#define T480MICORS (480 * TICKS_PER_US)

/* --- Schreibe "1" --- */
#define WRITE_ONE_LOW           (6 * TICKS_PER_US)     /* Bus auf Low halten        */
#define WRITE_ONE_HIGH          (64 * TICKS_PER_US)   /* Bus freigeben, dann warten */

/* --- Schreibe "0" --- */
#define WRITE_ZERO_LOW          (60 * TICKS_PER_US)   /* Bus auf Low halten        */
#define WRITE_ZERO_RELEASE      (10 * TICKS_PER_US)   /* Bus freigeben, dann warten */

/* --- Lese Bit --- */
#define READ_LOW            (6 * TICKS_PER_US)  /* Bus auf Low halten        */
#define READ_RELEASE        (9 * TICKS_PER_US)  /* Bus freigeben, warten     */
#define READ_SAMPLE        (55 * TICKS_PER_US)  /* Busabfrage + warten       */


/* --- Reset --- */
#define RESET_LOW         (480 * TICKS_PER_US)  /* Bus auf Low halten        */
#define RESET_RELEASE      (70  * TICKS_PER_US) /* Bus freigeben, warten     */
#define RESET_QUERY       (410 * TICKS_PER_US)   /* Busabfrage + warten       */



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

int impulsDelay(uint32_t Microsek){
TIM2 -> CNT = 0;
TIM2 -> CR1 |= 1U;
while(TIM2 -> CNT < Microsek){
}

TIM2 -> CR1 &= ~1U;
return 1;
}

int resetImpuls(){
pd0Low();
impulsDelay(RESET_LOW);
pd0High();
    
}

// EOF