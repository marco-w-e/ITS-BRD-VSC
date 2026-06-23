#include <locale.h>
#include <stdint.h>
#include "Output.h"
#include "timer.h"
#include "fehler.h"
#include "Typs.h"
#include "Input.h"
#include "lcd.h"


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
        if (write_bit((temp >> i) & 0x01) != WORKING) {
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

            if (d){

                crc ^= 0x8C;
            }
                

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
    GPIOD->OTYPER &= ~(1U << 0);     
    impulsDelay(750000 * 90);
    GPIOD->OTYPER |= (1U << 0);
           


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
/*
int OW_search(uint8_t *ROM_NUM,uint8_t *LastDeviceFlag,uint8_t *Lastdiscrepans){
uint8_t id_Byte;
uint8_t comp_Byte;
// i der index von der vorschleife enspricht id bit numbe
int id_bit_number;
uint8_t last_zero;
uint8_t search_di;
int rom_byte_number;
 // initialize for search
   id_bit_number = 0;
   last_zero = 0;
   rom_byte_number = 0;


    if(reset()!= WORKING){lcdPrintS("Kein sensor!\n");};
    if(*LastDeviceFlag == 1){
    write_byte(0xF0);
    
        for(;id_bit_number < 64; id_bit_number++){
            
            read(&id_Byte);
            read(&comp_Byte);
            
            if((id_Byte == 1) && (comp_Byte == 1)) return -1;
        //
            if((id_Byte == 0) && (comp_Byte == 0)){
                if(id_bit_number == *Lastdiscrepans){
                    search_di =1; 
                }
                else if (id_bit_number>*Lastdiscrepans) {
                search_di = 0;
                }else {
                
                ROM_NUM[id_bit_number] = search_di;
                }
                write_byte(search_di);
                if (search_di== 0) {
                last_zero = id_bit_number;
                
            }
        // 
            search_di = id_Byte;
            ROM_NUM[i] = search_di;

            
        }
        
        if (Lastdiscrepans == 0) {

        }else {
        *LastDeviceFlag = 1;
        }
    }
    if(crc_pruefen(ROM_NUM,8) == 1){
    return 1;

    }else{

        Lastdiscrepans = 0;
        LastDeviceFlag = 0;
    
        return -1;

    }

}
*/
int OW_searcht(uint8_t *ROM_NO,uint8_t *LastDeviceFlag,uint8_t *LastDiscrepancy){
    uint8_t id_bit ;
    uint8_t cmp_id_bit;
    uint8_t search_direction;
    uint8_t id_bit_number = 0;
    uint8_t rom_byte_number = 0;
    uint8_t rom_byte_mask = 1;
    uint8_t last_zero = 0;

 if(reset() != 1){
    return -1;

 }
    if(LastDeviceFlag == 1){
        return -2;
    }
    write_byte(0xF0);
    do {
        read(&id_bit);
        read(&cmp_id_bit);
        
        if (id_bit == 1 && cmp_id_bit == 1) {
            return -3 ;; // Fehler: Keine Geräte (Abbruch)
        } else {
            if (id_bit != cmp_id_bit) {
                // Keine Diskrepanz, Richtung ist eindeutig
                search_direction = id_bit;
            } else {
                // Diskrepanz auflösen
                if (id_bit_number < LastDiscrepancy) {
                    // Pfad aus dem vorherigen ROM-Eintrag übernehmen
                    search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
                } else {
                    // Wenn gleich, diesmal 1 wählen, ansonsten die standardmäßige 0
                    search_direction = (id_bit_number == LastDiscrepancy);
                }

                // Wenn der 0-Pfad gewählt wurde, Position merken
                if (search_direction == 0) {
                    last_zero = id_bit_number;
                    
                
                }
            }

            // Bit im ROM-Buffer setzen oder löschen
            if (search_direction == 1) {
                ROM_NO[rom_byte_number] |= rom_byte_mask;
            } else {
                ROM_NO[rom_byte_number] &= ~rom_byte_mask;
            }

            // Richtung an Slaves senden (trennt inkompatible Geräte ab)
            write_bit(search_direction);

            // Bit-Zähler und Masken weiterschalten
            id_bit_number++;
            rom_byte_mask <<= 1;
            if (rom_byte_mask == 0) {
                rom_byte_number++;
                rom_byte_mask = 1;
            }
        }
    } while(rom_byte_number < 8);
    
    if(crc_pruefen(ROM_NO,8) == 1){
    
    *LastDiscrepancy = last_zero;
    }
    if (LastDiscrepancy == 0) {
            *LastDeviceFlag = 1;
        }

return 1;

}
int OWFirst(int LastDiscrepancy,int LastDeviceFlag){
        LastDiscrepancy = 0;
        LastDeviceFlag = 0;

}
