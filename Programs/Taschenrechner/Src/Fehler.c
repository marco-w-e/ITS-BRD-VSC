 #include "stdio.h"
#include "limits.h"
#include "stdbool.h"
#include "Fehler.h"
#include "Stack.h"
#include "lcd.h"
#include "display.h"
#include "rechner.h"
#include "token.h"
#include "keypad.h"

void errorLoop(void){
           char i;     
        while(i!= CLEAR){
         i = getKeyPadInput();

        } 
        clear();
        setNormalMode();
        clearStdout();  
}
void refresh(int errorCode){
        
    switch(errorCode){
        case WORKING :
        break;
        case STACK_OVERFLOW : 
                setErrMode();   
                printStdout("STACK_OVERFLOW press Clear") ;
                 errorLoop();
                           
        break;
        case STACK_UNDERFLOW :
                setErrMode();   
                printStdout("STACK_UNDERFLOW") ;
                 errorLoop();
        break;
        case STACK_EMPTY :
                setErrMode();  
                printStdout("STACK_EMPTY") ;
                 errorLoop();
        break;
        case INT_OVERFLOW :
                setErrMode();   
                printStdout("INT_OVERFLOW press Clear") ;
                errorLoop();
                
        break;
        case INT_UNDERFLOW :
                setErrMode();   
                printStdout("INT_UNDERFLOW press Clear") ;
                 errorLoop();
        break;
        case ZERO_DIVISON :
                setErrMode();   
                printStdout("ZERO_DIVISON press Clear");
                 errorLoop();
        break;
        
    }

}