 #include "stdio.h"
#include "limits.h"
#include "stdbool.h"
#include "Fehler.h"
#include "Stack.h"
#include "lcd.h"
#include "display.h"



void refresh(int errorCode){

    switch(errorCode){
        case -1: 
                setErrMode();   
                printStdout("STACK_OVERFLOW press Clear") ;
                                
        break;
        case -2:
                setErrMode();   
                printStdout("STACK_UNDERFLOW") ;
                
        break;
        case -3:
                setErrMode();  
                printStdout("STACK_EMPTY") ;
                
        break;
        case -4:
                setErrMode();   
                printStdout("INT_OVERFLOW press Clear") ;
               
        break;
        case -5:
                setErrMode();   
                printStdout("INT_UNDERFLOW press Clear") ;
                
        break;
        case -6:
                setErrMode();   
                printStdout("ZERO_DIVISON press Clear");
                
        break;
        
    }

}