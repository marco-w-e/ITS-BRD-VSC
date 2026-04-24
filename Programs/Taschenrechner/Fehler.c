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
                setNormalMode();                
        break;
        case -2:
                setErrMode();   
                printStdout("STACK_UNDERFLOW") ;
                setNormalMode();
        break;
        case -3:
                setErrMode();  
                printStdout("STACK_EMPTY") ;
                setNormalMode();
        break;
        case -4:
                setErrMode();   
                printStdout("INT_OVERFLOW press Clear") ;
                setNormalMode();
        break;
        case -5:
                setErrMode();   
                printStdout("INT_UNDERFLOW press Clear") ;
                setNormalMode();
        break;
        case -6:
                setErrMode();   
                printStdout("ZERO_DIVISON press Clear");
                setNormalMode();
        break;
        
    }

}