/**
  ******************************************************************************
  * @file    Stack.c
  * @brief   Stack Implementierung - NUR push und pop als oeffentliche Funktionen.
  ******************************************************************************
  */

#include "stdio.h"
#include "limits.h"
#include "stdbool.h"
#include "Fehler.h"
#include "rechner.h"
#include "display.h"

#define MAX_CAPACITY 20

static int stack[MAX_CAPACITY];
static int top = -1;

int push(int *val)
{
    if (top >= MAX_CAPACITY - 1) return STACK_OVERFLOW;
    top++;
    stack[top] = *val;
    return WORKING;
}

int pop(int *val)
{
    if (top < 0) return STACK_EMPTY;
    *val = stack[top];
    top--;
    return WORKING;
}
