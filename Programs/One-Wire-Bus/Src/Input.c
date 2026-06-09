#include <stdint.h>
#include "Output.h"
#include "timer.h"




int read(uint8_t *input){
*input = GPIOD->IDR;
 return 1;
}