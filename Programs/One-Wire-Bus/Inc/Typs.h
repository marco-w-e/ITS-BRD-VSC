

#ifndef TYPS_H
#define	TYPS_H
#include <stdint.h>

typedef struct {
    uint8_t Crc;
    uint8_t SerialNum[6];
    uint8_t FamCode;

} ROM_Number;


typedef struct {
    uint8_t Crc;
    uint8_t SerialNum[6];
    uint8_t FamCode;

} Scratchpad;






#endif
// EOF

