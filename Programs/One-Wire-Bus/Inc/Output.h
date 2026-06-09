

#include <stdint.h>
#ifndef _Output_H
#define	_Output_H
#define TICKS_PER_US 90
#define T60MICROS (60 * TICKS_PER_US)
#define T480MICORS (480 * TICKS_PER_US)

#define PIN 0

/* --- Schreibe "1" --- */
#define WRITE_ONE_LOW           (6 * TICKS_PER_US)     /* Bus auf Low halten        */
#define WRITE_ONE_HIGH          (64 * TICKS_PER_US)   /* Bus freigeben, dann warten */

/* --- Schreibe "0" --- */
#define WRITE_ZERO_LOW          (60 * TICKS_PER_US)   /* Bus auf Low halten        */
#define WRITE_ZERO_RELEASE      (10 * TICKS_PER_US)   /* Bus freigeben, dann warten */

/* --- Lese Bit --- */
#define READ_LOW            (6 * TICKS_PER_US)  /* Bus auf Low halten        */
#define READ_RELEASE        (9 * TICKS_PER_US)  /* Bus freigeben, warten     */
#define READ_SAMPLE        (55 * TICKS_PER_US)  /* Busabfrage + warten       */


/* --- Reset --- */
#define RESET_LOW         (480 * TICKS_PER_US)  /* Bus auf Low halten        */
#define RESET_RELEASE      (70  * TICKS_PER_US) /* Bus freigeben, warten     */
#define RESET_QUERY       (410 * TICKS_PER_US)   /* Busabfrage + warten       */


int oneWireSetup(void);

int pd1High(void);

int pd0High(void);

int pd0Low(void);

int oneWireSetup(void);

int impulsDelay(uint32_t Microsek);
int resetImpuls();

#endif
// EOF
