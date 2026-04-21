

#include "stdio.h"
#include "limits.h"
#include "stdbool.h"
#include "Fehler.h"
#include "Stack.h"
#include "lcd.h"
#include "display.h"


#define MAX_LENGHT_STR 20

char intToString (int zahl,char *str){
    int vorzeichen = zahl; //vorzeichen merken für ausgabe
    int i =0;
    if(zahl<0)zahl = -zahl; // mach positiv zahl = -zahl;

    while(zahl > 0){ // ein ziffer in char rein
       str[i++] = zahl % 10 + '0';
       zahl /= 10; 
    }
    if(vorzeichen < 0){ // vorzeich rauf wenn gibt 

        str[i++]='-';
    }
    str[i]='\0' ;// string ende
    for(int y = 0, x = i-1;y<x;y++,x--){
        char ablage = str[y];
        str[y] = str[x];
        str[x] = ablage;

    }


}


int plus(void){
    int x;
    int y;
    char str [20];
    pop(&x);
    pop(&y);
    if(x == INT_MAX && y>0 || y == INT_MAX && x>0) return INT_OVERFLOW;
    if(x == INT_MIN && y<0 || y == INT_MIN && x<0) return INT_UNDERFLOW;
    if(x > INT_MAX /2 && y > INT_MAX /2 ) return INT_OVERFLOW;
    if(x > INT_MIN /2 && y < INT_MIN /2 ) return INT_UNDERFLOW;
    int result = x + y;
    clearStdout();
    intToString(result,str);
     printStdout(str);
    push(&result);
    return WORKING;
} 
int minus (void){
    int x;
    int y;
     pop(&x);
     pop(&y);
     int result = x - y;
    lcdPrintInt(result);
    push(&result);
    return WORKING;
}
int mal(void){
    int x;
    int y;
     pop(&x);
     pop(&y);
     int result = x * y;
    lcdPrintInt(result);
    push(&result);
    return WORKING;

}
int geteilt(void){
    int x;
    int y;
     pop(&x);
     pop(&y);
     if(x < y) return ZERO_DIVISON;
     if (x == 0) return ZERO_DIVISON;
     int result = x * y;
    lcdPrintInt(result);
    push(&result);
    return WORKING;
}



int printZeichen(void){
    int number;
    char str [20];
    peek(&number);
    clearStdout();
    intToString(number,str);
    printStdout(str);
    return WORKING;

    

    
}

int swap(void){
 int x ;
 int y ;
 pop(&x);
 pop(&y);
 push(&x);
 push(&y);
    
}

int clear(void){
 clearStack();
 return WORKING;

}

int printAlles(void){
    int numbers[20];
    char str[20];

    peekALL (numbers);
    for(int i =0;i<=20;i++){

         intToString(numbers[i],str);
         printStdout(str);
        
    }
   

}






