#include <locale.h>
#include <stdint.h>
#include "Output.h"
#include "timer.h"
#include "fehler.h"
#include "Typs.h"
#include "Input.h"


int read(uint8_t *input){

    if (input == NULL){
        return -1;
    }

pd0Low();
impulsDelay(READ_LOW);

pd0High();
impulsDelay(READ_RELEASE);

*input = (GPIOD->IDR >> PIN) & 0x01;

impulsDelay(READ_SAMPLE);
return WORKING;
}

int read_byte(uint8_t *byte)
{
    if (byte == NULL) {
        return -1;
    }

    *byte = 0;

    for (uint8_t i = 0; i < 8; i++) {
        uint8_t bit = 0;

        pd0Low();
        impulsDelay(READ_LOW);
        pd0High();
        impulsDelay(READ_RELEASE);
        bit = (GPIOD->IDR >> PIN) & 0x01;
        impulsDelay(READ_SAMPLE);

        *byte |= (bit << i);  
    }

    return WORKING;
}




int rom_read(uint8_t *rom)
{
    if (rom == NULL)
        return -1;

    for (int i = 0; i < 8; i++)
    {
        rom[i] = 0;
    }

    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            uint8_t bit;

            if (read(&bit) != WORKING)
                return -1;

            rom[i] |= (bit << j);
        }
    }

    return WORKING;
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

    return WORKING;  // Sensor vorhanden 
}

int write_bit(uint8_t bit)
{
    if (bit == 1){
        pd0Low();
        impulsDelay(WRITE_ONE_LOW);

        pd0High();
        impulsDelay(WRITE_ONE_HIGH);

        
    }
    else if (bit == 0){
        pd0Low();
        impulsDelay(WRITE_ZERO_LOW);

        pd0High();
        impulsDelay(WRITE_ZERO_RELEASE);

       
    }
    else{
        return -1;
    }
 return WORKING;
}

int write_byte(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++){
       uint8_t temp = byte;
        if (write_bit((temp >> i) & 0x01) != 1) {
            return -1;
        }

    }
        return WORKING;

}

uint8_t crc_berechnen(uint8_t *daten, uint8_t laenge)
{
    uint8_t crc = 0;

    for (uint8_t i = 0; i < laenge; i++)
    {
        uint8_t byte = daten[i];

        for (uint8_t j = 0; j < 8; j++)
        {
            uint8_t d = (crc ^ byte) & 0x01;

            crc >>= 1;

            if (d)
                crc ^= 0x8C;

            byte >>= 1;
        }
    }

    return crc;
}

int crc_pruefen(uint8_t *rom, uint8_t laenge)
{
    if (rom == NULL)
        return -1;

    if (laenge < 2)
        return -1;

    uint8_t crc = crc_berechnen(rom, laenge - 1);

    if (crc != rom[laenge - 1])
        return -1;

    return WORKING;
}

int temperatur_lesen(uint8_t *sensor_rom, float *temperatur){

    if (temperatur == NULL){

        return -1;
    }
    
    //MEssung
    reset(); // Checken Ob Sensor vorhanden ist.
    write_byte(MATCH_ROM);
    for(uint8_t i = 0; i < 8; i++){
         write_byte(sensor_rom[i]);
        
        
        
    }
    write_byte(CONVER_T);
    pd1High();           
    impulsDelay(750000);



    reset();
    write_byte(MATCH_ROM);
    for(uint8_t i = 0; i < 8; i++){
         write_byte(sensor_rom[i]);
    }
    write_byte(READ_SPAD);
    uint8_t scratchpad[9];
    for (uint8_t i = 0; i < 9; i++) {
        read_byte(&scratchpad[i]);
    }

    if(crc_pruefen(scratchpad, 9) != WORKING){
        return -1;
    };

    int16_t rohwert = (int16_t)((scratchpad[1] << 8) | scratchpad[0]);
    *temperatur = rohwert / 16.0f;

    return WORKING;


};
