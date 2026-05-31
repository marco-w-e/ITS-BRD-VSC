#include "button.h"
#include "error.h"
#include "stm32f4xx.h"
#include <stdbool.h>
#include "lcd.h"

void wartenBisKnopfDruck(void)
{
    while(1)  // Endlosschleife
    {
        if((GPIOF->IDR & 0xFFU) != 0xFFU)  // Prüfe ob NICHT alle Bits 1 sind
        {
            break;  
        }
    }
}