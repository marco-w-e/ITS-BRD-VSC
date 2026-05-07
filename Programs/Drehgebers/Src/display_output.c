/**
 ******************************************************************************
 * @note    Aufgabe 2 - Drehgeber
 * @file    display_output.c
 * @author  Dylan Dagomber 2815132, Marco Weidner
 * @date    03.05.2026
 * @brief
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "display_output.h"
#include "display.h"
#include "fehler.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>

int intToString(int zahl, char *str) {

  int vorzeichen = zahl;
  int i = 0;

  if (zahl == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return WORKING;
  }

  if (zahl < 0) {
    zahl = -zahl;
  }

  while (zahl > 0) {
    str[i++] = (zahl % 10) + '0';
    zahl /= 10;
  }

  if (vorzeichen < 0) {
    str[i++] = '-';
  }

  str[i] = '\0';

  for (int y = 0, x = i - 1; y < x; y++, x--) {
    char ablage = str[y];
    str[y] = str[x];
    str[x] = ablage;
  }

  return WORKING;
}

int displayDrehwinkel(int drehwinkel) {

  char str[20];

  clearStdout();

  intToString(drehwinkel, str);

  strcat(str, " Grad");

  printStdout(str);

  return WORKING;
}

int displayDrehgeschwindigkeit(int drehgeschwindigkeit) {

  char str[20];

  clearStdout();

  intToString(drehgeschwindigkeit, str);

  strcat(str, " Grad/s");

  printStdout(str);

  return WORKING;
}