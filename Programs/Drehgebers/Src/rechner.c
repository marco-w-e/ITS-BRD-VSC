#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "input.h"
typedef enum {
    IDEL,
    FORWARD,
    BACKWARD,
    ERRO,
}Direction;

static const Direction  matrix[4][4]{
{IDEL,BACKWARD,FORWARD,ERRO}
{FORWARD,IDLE,ERRO,BACKWARD}
{BACKWARD,ERRO,IDLE,FORWARD}
{ERRO,FORWARD,BACKWARD,IDLE}
}

getDirection(oldPhase,Phase){
    
}