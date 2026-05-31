#ifndef BUTTON_H
#define BUTTON_H


/**
 * @brief Wartet bis ein beliebiger Knopf (S0-S7) gedrückt wird
 * 
 * Diese Funktion blockiert die Programmausführung und kehrt erst zurück,
 * wenn einer der Knöpfe S0 bis S7 gedrückt wurde.
 * 
 * Die Knöpfe sind low-aktiv (0 = gedrückt, 1 = nicht gedrückt).
 * 
 * @return void
 */
void wartenBisKnopfDruck(void);

#endif /* BUTTON_H */