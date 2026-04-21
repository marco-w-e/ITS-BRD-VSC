/**
  ******************************************************************************
  * @file    Stack.c
  * @author  Marco Weidner
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

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
    if(top >= MAX_CAPACITY) return STACK_OVERFLOW;
    top++;
    stack[top] = *val;
    return WORKING;

}
int pop(int *val)
{
    if(top < 0) return STACK_EMPTY;
    *val = stack[top];
     top--;
    return WORKING;
}
int  peek(int *val)
{
    
    if(top < 0) return STACK_EMPTY;
    *val = stack[top];
    return WORKING;

}
int peekALL (int *x)
{   
    if(top < 0 ) return STACK_EMPTY;
    int i = top;
    
    while(i != -1){
        x[i]=stack[i];
        i--;
    }
    return WORKING;
}
int clearStack (){
    if(top < 0 ) return STACK_EMPTY;
    int i = top;
    int x;
    
    while (i != -1){
        pop(&x);
    }
    return WORKING;
}
