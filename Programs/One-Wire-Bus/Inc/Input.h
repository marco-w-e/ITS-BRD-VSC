#include <stdint.h>
#include "Output.h"
#include "Typs.h"
#ifndef INPUT_H
#define	INPUT_H

/* --- Temperatur Sensor --- */
#define MATCH_ROM       0x55
#define CONVER_T        0x44 
#define READ_ROM        0x33
#define READ_SPAD       0xBE
#define SEARCH_ROM      0xF0

#define TEMP_TIME       (410 * 90)   /* Busabfrage + warten       */





int read(uint8_t *input);

int rom_read(uint8_t *rom);

int write_bit(uint8_t bit);

int reset();

int write_byte(uint8_t byte);

uint8_t crc_berechnen(uint8_t *daten, uint8_t laenge);

int crc_pruefen(uint8_t *daten, uint8_t laenge);

int read_byte(uint8_t *byte);

int temperatur_lesen(uint8_t *sensor_rom, float *temperatur);

int OW_search(uint8_t *ROM_NUM,uint8_t *LastDeviceFlag,uint8_t *Lastdiscrepans);

#endif
// EOF

