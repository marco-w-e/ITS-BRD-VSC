

#include <stdint.h>
#ifndef _Output_H
#define	_Output_H
#define TICKS_PER_US 90
#define T60MICROS (60 * TICKS_PER_US)
#define T480MICORS (480 * TICKS_PER_US)

int oneWireSetup(void);

int pd1High(void);

int pd0High(void);

int pd0Low(void);

int oneWireSetup(void);

int impulsDelay(uint32_t Microsek);
int resetImpuls();

#endif
// EOF
