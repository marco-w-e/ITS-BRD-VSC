#ifndef BMP_H
#define BMP_H

/**
 * @brief Lädt das nächste BMP-Bild und zeigt es auf dem Display an.
 *
 * Reihenfolge der internen Schritte:
 *  1. Display leeren (weißer Hintergrund)
 *  2. Nächste Datei öffnen
 *  3. BMP-Dateiheader lesen und validieren
 *  4. BMP-Informationsheader lesen und validieren
 *  5. Bildgröße gegen Displayauflösung prüfen
 *  6. Farbtabelle einlesen (nur bei 8-bit-Bildern)
 *  7. Pixeldaten dekodieren und zeilenweise ausgeben
 *  8. Ressourcen freigeben
 *
 * Bei einem Fehler in einem der Schritte wird die Funktion vorzeitig
 * beendet; das Display kann dann einen unvollständigen Inhalt zeigen.
 */
void bmp_displayNext(void);

#endif 