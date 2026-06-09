#include <stdint.h>
#include "Output.h"
#ifndef INPUT_H
#define	INPUT_H





int read(uint8_t *input);


int rom_read(uint64_t *rom);

int write_bit(uint8_t bit);

int reset();

int write_byte(uint8_t byte);

#endif
// EOF