/**
 * @file BMP.c
 * @brief BMP-Bilddekodierung und Darstellung auf einem LCD-Display.
 *
 * Unterstützt unkomprimierte (24-bit) und palettierte (8-bit) BMP-Dateien,
 * sowie RLE8-komprimierte Bitmaps.
 */

#include "BMP.h"
#include "BMP_types.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "errorhandler.h"
#include "input.h"
#include "lcd.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------
 * Konstanten
 * ---------------------------------------------------------------------- */

#define DISPLAY_HEIGHT      480
#define DISPLAY_WIDTH       320
#define BMP_PALETTE_SIZE    256
#define BMP_SIGNATURE       0x4D42  // 'BM' als Little-Endian-Wert
#define BMP_INFOHEADER_SIZE 40      // Standard BITMAPINFOHEADER (40 Byte)
#define BITS_PER_BYTE       8

/* -------------------------------------------------------------------------
 * Modulinterne Zustandsvariablen
 * ---------------------------------------------------------------------- */

static BITMAPFILEHEADER fileHeader;
static BITMAPINFOHEADER infoHeader;
static RGBQUAD         *palette = NULL;

/* -------------------------------------------------------------------------
 * Farbkonvertierung: BGR → RGB565
 * ---------------------------------------------------------------------- */

/**
 * @brief Konvertiert 8-bit RGB-Werte in das RGB565-Format des Displays.
 */
static uint16_t toRGB565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

/**
 * @brief Liest eine Farbe aus der Farbtabelle anhand eines Palettenindex.
 */
static uint16_t colorFromPaletteIndex(uint8_t index) {
    if (palette == NULL) {
        return 0;
    }
    return toRGB565(
        palette[index].rgbRed,
        palette[index].rgbGreen,
        palette[index].rgbBlue
    );
}

/**
 * @brief Liest eine Farbe direkt aus einem 24-bit RGB-Pixel.
 */
static uint16_t colorFromRGBTriple(RGBTRIPLE *pixel) {
    return toRGB565(pixel->rgbtRed, pixel->rgbtGreen, pixel->rgbtBlue);
}

/* -------------------------------------------------------------------------
 * Zeilenpuffer-Hilfsfunktionen
 * ---------------------------------------------------------------------- */

/**
 * @brief Schreibt den Zeilenpuffer auf das Display.
 *
 * @param buffer      Pixeldaten der aktuellen Zeile.
 * @param pixelCount  Anzahl der gültigen Pixel im Puffer.
 * @param y           Y-Koordinate (Displayzeile).
 */
static void flushLineBuffer(COLOR *buffer, int pixelCount, int y) {
    bool yInRange     = (y >= 0 && y < DISPLAY_WIDTH);
    bool hasPixels    = (pixelCount > 0);

    if (!hasPixels || !yInRange) {
        return;
    }

    Coordinate start = {0, (uint16_t)y};
    LENGTH length    = (pixelCount < DISPLAY_HEIGHT) ? (LENGTH)pixelCount
                                                      : DISPLAY_HEIGHT;
    GUI_WriteLine(start, length, buffer);
}

/**
 * @brief Setzt alle Einträge eines Puffers auf Weiß (Hintergrundfarbe).
 */
static void clearLineBuffer(COLOR *buffer, int size) {
    for (int i = 0; i < size; i++) {
        buffer[i] = WHITE;
    }
}

/* -------------------------------------------------------------------------
 * Header- und Paletten-Einlesen
 * ---------------------------------------------------------------------- */

/**
 * @brief Liest den BMP-Dateiheader und prüft die Signatur.
 */
static int readFileHeader(void) {
    size_t bytesRead = COMread((char *)&fileHeader, sizeof(BITMAPFILEHEADER), 1);
    RETURN_NOK_ON_ERR(bytesRead != 1,           "konnte nicht gelesen werden");
    RETURN_NOK_ON_ERR(fileHeader.bfType != BMP_SIGNATURE, "BMP-Datei ist nicht bgültig");
    return EOK;
}

/**
 * @brief Liest den BMP-Informationsheader und validiert dessen Inhalt.
 *
 * Geprüft werden: Headergröße, Farbtiefe (8 oder 24 bit) und Kompression
 * (unkomprimiert oder RLE8).
 */
static int readInfoHeader(void) {
    size_t bytesRead = COMread((char *)&infoHeader, sizeof(BITMAPINFOHEADER), 1);
    RETURN_NOK_ON_ERR(bytesRead != 1, "InfoHeader konnte nichjt gelesen werden");
    RETURN_NOK_ON_ERR(infoHeader.biCompression != BI_RGB &&
                      infoHeader.biCompression != BI_RLE8,
                      "Kompression ist nicht unterstützte ");
    
    RETURN_NOK_ON_ERR(infoHeader.biBitCount != 8 && infoHeader.biBitCount != 24,
                      "Farbtiefe ist nicht 8 oder 24 bit");
    RETURN_NOK_ON_ERR(infoHeader.biSize != BMP_INFOHEADER_SIZE,
                      "InfoHeader-Größe Ungülltig");
    return EOK;
}

/**
 * @brief Liest die Farbtabelle (Palette) für 8-bit-Bilder.
 *
 * Die Anzahl der Einträge ergibt sich aus biClrUsed (oder 256, falls 0).
 */
static int palletteAuslesen(void) {
    uint32_t numColors = (infoHeader.biClrUsed == 0)
                         ? BMP_PALETTE_SIZE
                         : infoHeader.biClrUsed;

    palette = (RGBQUAD *)malloc(numColors * sizeof(RGBQUAD));
    if (palette == NULL) {
        return ERROR_BMP_MEMORY;
    }

    size_t bytesRead = COMread((char *)palette, sizeof(RGBQUAD), numColors);
    RETURN_NOK_ON_ERR(bytesRead != numColors, "Fehler beim Einlesen der Farbtabelle!");

    return EOK;
}

/**
 * @brief Gibt den Palettenspeicher frei und setzt den Zeiger zurück.
 */
static void paletteFreien(void) {
    free(palette);
    palette = NULL;
}

/* -------------------------------------------------------------------------
 * Validierung
 * ---------------------------------------------------------------------- */

/**
 * @brief Prüft, ob die Bildmaße die Displaygrenzen einhalten.
 */
static int dimensionenChecken(void) {
    if (infoHeader.biWidth  > DISPLAY_HEIGHT ||
        infoHeader.biHeight > DISPLAY_WIDTH) {
        return ERROR_BMP_SIZE_LIMIT;
    }
    return EOK;
}

/* -------------------------------------------------------------------------
 * Pixeldekodierung – RLE8
 * ---------------------------------------------------------------------- */

/**
 * @brief Dekodiert eine RLE8-komprimierte Bitmap zeilenweise auf das Display.
 *
 * Verarbeitet Wiederholungs-, Escape- und absoluten Modus gemäß BMP-Standard.
 */
static int decodeRLE8(void) {
    COLOR lineBuffer[DISPLAY_HEIGHT];
    clearLineBuffer(lineBuffer, DISPLAY_HEIGHT);

    int  x         = 0;
    int  y         = infoHeader.biHeight - 1;  // BMP ist von unten nach oben gespeichert
    bool finished  = false;

    while (!finished) {
        uint8_t count = nextChar();   // Wiederholungsanzahl oder 0 (Escape)
        uint8_t value = nextChar();   // Farbindex oder Escape-Code

        if (count > 0) {
            /* --- Wiederholungsmodus: 'count' Pixel mit Farbe 'value' --- */
            uint16_t color = colorFromPaletteIndex(value);
            for (int i = 0; i < count; i++) {
                if (x < DISPLAY_HEIGHT) {
                    lineBuffer[x] = color;
                }
                x++;
            }
        } else {
            /* --- Escape-Modus --- */
            switch (value) {
                case 0:  /* Zeilenende (EOL) */
                    flushLineBuffer(lineBuffer, x, y);
                    clearLineBuffer(lineBuffer, DISPLAY_HEIGHT);
                    x = 0;
                    y--;
                    break;

                case 1:  /* Bitmap-Ende (EOF) */
                    flushLineBuffer(lineBuffer, x, y);
                    finished = true;
                    break;

                case 2:  /* Delta: Position relativ verschieben */
                    x += nextChar();
                    y -= nextChar();
                    break;

                default:  /* Absoluter Modus: 'value' einzelne Pixelindizes folgen */
                    for (int i = 0; i < value; i++) {
                        uint8_t  index = nextChar();
                        uint16_t color = colorFromPaletteIndex(index);
                        if (x < DISPLAY_HEIGHT) {
                            lineBuffer[x] = color;
                        }
                        x++;
                    }
                    /* Padding: absolute Blöcke sind auf 2-Byte-Grenzen ausgerichtet */
                    if (value % 2 != 0) {
                        nextChar();
                    }
                    break;
            }
        }
    }

    return EOK;
}

/* -------------------------------------------------------------------------
 * Pixeldekodierung – unkomprimiert (8-bit Palette / 24-bit RGB)
 * ---------------------------------------------------------------------- */

/**
 * @brief Berechnet das Zeilen-Padding eines unkomprimierten BMP.
 *
 * BMP-Zeilen sind auf 4-Byte-Grenzen aufgefüllt.
 *
 * @param bytesPerPixel Byte pro Pixel (1 bei 8-bit, 3 bei 24-bit).
 * @return Anzahl der Padding-Bytes am Zeilenende.
 */
static int reihenPadding(int bytesPerPixel) {
    int rowBytes = (((infoHeader.biWidth * infoHeader.biBitCount) + 31) / 32) * 4;
    return rowBytes - (infoHeader.biWidth * bytesPerPixel);
}

/**
 * @brief Liest einen einzelnen Pixel und gibt dessen RGB565-Farbe zurück.
 *
 * @param bitDepth Farbtiefe (8 oder 24).
 */
static uint16_t nächstenPixelColor(int bitDepth) {
    if (bitDepth == 8) {
        uint8_t index = nextChar();
        return colorFromPaletteIndex(index);
    }

    /* 24-bit */
    RGBTRIPLE pixel;
    COMread((char *)&pixel, sizeof(RGBTRIPLE), 1);
    return colorFromRGBTriple(&pixel);
}

/**
 * @brief Dekodiert eine unkomprimierte Bitmap (8-bit oder 24-bit).
 *
 * BMP speichert Zeilen von unten nach oben; die Darstellung wird entsprechend
 * gespiegelt.
 */
static int decodeUncompressed(void) {
    int   bytesPerPixel = infoHeader.biBitCount / BITS_PER_BYTE;
    int   padding       = reihenPadding(bytesPerPixel);
    int   drawWidth     = (infoHeader.biWidth < DISPLAY_HEIGHT)
                          ? infoHeader.biWidth
                          : DISPLAY_HEIGHT;
    COLOR lineBuffer[DISPLAY_HEIGHT];

    for (int row = 0; row < infoHeader.biHeight; row++) {
        /* BMP-Zeile 0 = unterste Bildzeile → Display von oben */
        int displayY = (infoHeader.biHeight - 1) - row;

        /* Pixeldaten der Zeile lesen */
        for (int col = 0; col < drawWidth; col++) {
            lineBuffer[col] = nächstenPixelColor(infoHeader.biBitCount);
        }

        /* Pixel außerhalb der Zeichenbreite (falls Bild breiter als Display) überspringen */
        int remainingPixels = infoHeader.biWidth - drawWidth;
        for (int i = 0; i < remainingPixels; i++) {
            nächstenPixelColor(infoHeader.biBitCount);
        }

        /* Padding-Bytes überspringen */
        for (int i = 0; i < padding; i++) {
            nextChar();
        }

        flushLineBuffer(lineBuffer, drawWidth, displayY);
    }

    return EOK;
}

/* -------------------------------------------------------------------------
 * Öffentliche Funktion
 * ---------------------------------------------------------------------- */

/**
 * @brief Lädt und zeigt das nächste BMP-Bild auf dem Display an.
 *
 * Liest Header, Palette (bei 8-bit) und Pixeldaten über die serielle
 * Schnittstelle. Gibt nach der Darstellung alle Ressourcen frei.
 */
void bmp_displayNext(void) {
    GUI_clear(WHITE);
    openNextFile();

    if (readFileHeader()    != EOK) return;
    if (readInfoHeader()    != EOK) return;
    if (dimensionenChecken()!= EOK) return;

    /* Farbtabelle nur bei palettierten Bildern einlesen */
    if (infoHeader.biBitCount == 8) {
        if (palletteAuslesen() != EOK) {
            paletteFreien();
            return;
        }
    }

    /* Pixeldaten dekodieren */
    if (infoHeader.biCompression == BI_RLE8) {
        decodeRLE8();
    } else {
        decodeUncompressed();
    }

    paletteFreien();
}