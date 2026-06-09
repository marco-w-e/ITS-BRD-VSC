#include <stdint.h>
#include "Output.h"
#include "timer.h"
#include "fehler.h"




int read(uint8_t *input){

    if (input == NULL){
        return -1;
    }

pd0Low();
impulsDelay(READ_SAMPLE);

pd0High();
impulsDelay(READ_RELEASE);

*input = (GPIOD->IDR >> PIN) & 0x01;

impulsDelay(READ_SAMPLE);
return 1;
}


int rom_read(uint64_t *rom)
{
    if (rom == NULL) {
        return -1;
    }

    *rom = 0;

    for (uint8_t i = 0; i < 64; i++) {
        uint8_t bit = 0;

        if (read(&bit) != 0) {
            return -1;
        }

        *rom |= ((uint64_t)bit << i);
    }

    return 1;
}

int reset(){
    uint8_t praesenz = 0;

    pd0Low();
    impulsDelay(RESET_LOW);        

    pd0High();
    impulsDelay(RESET_RELEASE);   

    praesenz = (GPIOD->IDR >> PIN) & 0x01;  

    impulsDelay(RESET_QUERY);   

    if (praesenz == 1) {
        return -1;  // Kein Sensor angeschlossen 
    }

    return 0;  // Sensor vorhanden 
}