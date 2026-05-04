
#include "error.h"
#include "stm32f4xx.h"
#include <stdbool.h>
#include "lcd.h"


int gpioAusLesen(){

    return GPIOF->IDR & (0x03U);

}