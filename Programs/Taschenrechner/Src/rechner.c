

#include "Fehler.h"
#include "Stack.h"
#include "display.h"
#include "lcd.h"
#include "limits.h"
#include "stdbool.h"
#include "stdio.h"

#define MAX_LENGHT_STR 20

int intToString(int zahl, char *str) {
  int vorzeichen = zahl; // vorzeichen merken für ausgabe
  int i = 0;

  if (zahl == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return WORKING;
  }
  if (zahl < 0)
    zahl = -zahl; // mach positiv zahl = -zahl;

  while (zahl > 0) { // ein ziffer in char rein
    str[i++] = zahl % 10 + '0';
    zahl /= 10;
  }
  if (vorzeichen < 0) { // vorzeich rauf wenn gibt

    str[i++] = '-';
  }
  str[i] = '\0'; // string ende
  for (int y = 0, x = i - 1; y < x; y++, x--) {
    char ablage = str[y];
    str[y] = str[x];
    str[x] = ablage;
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
  if (err1 != 0)
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
  if (err1 != 0)
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
int mal(void) {
  int x;
  int y;
  char str[20];

  int err1 = pop(&x);
  if (err1 != 0)
    return err1;

  int err2 = pop(&y);
  if (err1 != 0)
    return err2;

  // Wenn X Positiv ist
  if (x > 0 && (y > (INT_MAX / x))) {
    return INT_OVERFLOW;
  }
  if (x > 0 && (y < INT_MIN / x)) {
    return INT_UNDERFLOW;
  }

  // Wenn X Negativ ist---
  if (y < 0 && y < INT_MAX / x) {
    return INT_OVERFLOW;
  }

  if (y > 0 && y > INT_MIN / x) {
    return INT_UNDERFLOW;
  }

  int result = x * y;
  clearStdout();
  intToString(result, str);
  printStdout(str);
  refresh(push(&result));
  return WORKING;
}

int geteilt(void) {
  int x;
  int y;
  char str[20];

  int err1 = pop(&x);
  if (err1 != 0)
    return err1;

  int err2 = pop(&y);
  if (err1 != 0)
    return err2;

  if (x == 0 || y == 0) {
    return ZERO_DIVISON;
  }

  int result = y / x;
  clearStdout();
  intToString(result, str);
  printStdout(str);
  refresh(push(&result));
  return WORKING;
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
  if (err1 != 0)
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

int printAlles(void) {
  int numbers[20];
  char str[20];
  int top;
  clearStdout();

  int err1 = peekALL(numbers, &top);
  if (err1 < 0)
    return err1;

  for (int i = 0; i < top; i++) {
    intToString(numbers[i], str);
    printStdout(str);
    printStdout(" "); // optional für Abstand
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
