#pragma once
#include <Adafruit_ILI9341.h>

/*
    DisplayManager kapselt das TFT-Display.

    Vorteil:
    - main.cpp kennt keine Display-Details
    - Hardware-Zugriffe sind an einer Stelle gebündelt
*/
class DisplayManager {
public:
    DisplayManager(uint8_t cs, uint8_t dc, uint8_t rst);

    // Initialisiert das Display
    void begin();

    // Liefert eine Referenz auf das TFT-Objekt
    Adafruit_ILI9341& tft();

private:
    Adafruit_ILI9341 _tft;
};
