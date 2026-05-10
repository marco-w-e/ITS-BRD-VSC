

#include "Fehler.h"
#include "Stack.h"
#include "display.h"
#include "lcd.h"
#include "limits.h"
#include "stdbool.h"
#include "stdio.h"

#define MAX_LENGHT_STR 20

int intToString(int zahl, char *str)
{
    int i = 0;

    if (zahl == 0) {
        str[i++] = '0';
        str[i]   = '\0';
        return WORKING;
    }
    int negativ = (zahl < 0);

    while (zahl != 0) {
        int ziffer = zahl % 10;
        if (ziffer < 0) ziffer = -ziffer;
        str[i++] = ziffer + '0';
        zahl /= 10;
    }

    if (negativ) {
        str[i++] = '-';
    }

    str[i] = '\0';

    /* String umkehren */
    for (int links = 0, rechts = i - 1; links < rechts; links++, rechts--) {
        char tmp       = str[links];
        str[links]     = str[rechts];
        str[rechts]    = tmp;
    }

    return WORKING;
}

int peek(int *val)
{
    int err = pop(val);
    if (err != WORKING) return err;
    return push(val);
}


int clearStack(void)
{
    int temp;
    int err = pop(&temp);
    while (err == WORKING) {
        err = pop(&temp);
    }
    return WORKING;
}


int plus(void) {
  int x;
  int y;
  char str[20];

  int err1 = pop(&x); // das was du da siehst ist für die fehler weiter gaben
                      // nennt man guard clause oder so idk :)
  if (err1 != 0)
    return err1; // hab das jetzt eigentlich jetzt bei jedem stack methoden
                 // aufruf gemacht

  int err2 = pop(&y);
  if (err2 != 0)
    return err2;

  if (x > 0 && y > INT_MAX - x) {
    return INT_OVERFLOW;
  }

  if (x < 0 && y < INT_MIN - x) {
    return INT_UNDERFLOW;
  }

  int result = x + y;
  clearStdout();
  intToString(result, str);
  printStdout(str);
  push(&result);
  return WORKING;
}
int minus(void) {
  int x;
  int y;
  char str[20];

  int err1 = pop(&x);
  if (err1 != 0)
    return err1;

  int err2 = pop(&y);
  if (err2 != 0)
    return err2;

  if (y > 0 && x < INT_MIN + y) {
    return INT_UNDERFLOW;
  }

  if (y < 0 && x > INT_MAX + y) {
    return INT_OVERFLOW;
  }

  int result = x - y;
  clearStdout();
  intToString(result, str);
  printStdout(str);
  refresh(push(&result));
  return WORKING;
}

int mal(void)
{
    int x;
    int y;
    char str[MAX_LENGTH_STR];

    int err = pop(&x);
    if (err != WORKING) return err;

    err = pop(&y);
    if (err != WORKING) return err;

    if (x == 0 || y == 0) {
        int result = 0;
        clearStdout();
        intToString(result, str);
        printStdout(str);
        return push(&result);
    }

    if (x > 0 && y > 0) {
        if (y > INT_MAX / x) return INT_OVERFLOW;
    } else if (x < 0 && y < 0) {
        if (y < INT_MAX / x) return INT_OVERFLOW;
    } else if (x > 0 && y < 0) {
        if (y < INT_MIN / x) return INT_UNDERFLOW;
    } else {
        if (x < INT_MIN / y) return INT_UNDERFLOW;
    }

    int result = x * y;
    clearStdout();
    intToString(result, str);
    printStdout(str);
    return push(&result);
}

int geteilt(void)
{
    int x;
    int y;
    char str[MAX_LENGTH_STR];

    int err = pop(&x);
    if (err != WORKING) return err;

    err = pop(&y);
    if (err != WORKING) return err;

    if (x == 0) return ZERO_DIVISON;

    if (y == INT_MIN && x == -1) return INT_OVERFLOW;

    int result = y / x;
    clearStdout();
    intToString(result, str);
    printStdout(str);
    return push(&result);
}

int printZeichen(void) {

  int number;
  char str[20];

  int err1 = peek(&number);
  if (err1 != 0)
    return err1;

  clearStdout();
  intToString(number, str);
  printStdout(str);
  return WORKING;
}

int swap(void) {

  int x;
  int y;
  int err1 = pop(&x);
  if (err1 != 0)
    return err1;

  int err2 = pop(&y);
  if (err2 != 0)
    return err2;

  push(&x);
  push(&y);
  return WORKING;
}

int clear(void) {
  setNormalMode();
  int err1 = clearStack();
  if (err1 != 0)
    return err1;
  clearStdout();
  return WORKING;
}
int peekALL(int *numbers,int *size){
  int val;
  int i;
  while(pop(&val)== WORKING){
      numbers[i] = val;
      i++ ;
  }
  *size = i;
}


int printAlles(void)
{
    int numbers[MAX_CAPACITY];
    int size = 0;
    char str[MAX_LENGTH_STR];

    int val;
    while (pop(&val) == WORKING) {
        numbers[size] = val;
        size++;
    }

    /* Stack wiederherstellen - umgekehrt pushen */
    for (int i = size - 1; i >= 0; i--) {
        int err = push(&numbers[i]);
        if (err != WORKING) return err;
    }

    /* Wenn Ausgabe: numbers[0] war oben */
    clearStdout();
    for (int i = 0; i < size; i++) {
        intToString(numbers[i], str);
        printStdout(str);
        printStdout(" ");
    }

    return WORKING;
}
int verdoppleTop(void) {
  int x;
  int err1 = peek(&x);
  if (err1 != 0)
    return err1;
  push(&x);
  return WORKING;
}


