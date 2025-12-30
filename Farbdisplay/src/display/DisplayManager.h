#pragma once
#include <Adafruit_ILI9341.h>

class DisplayManager {
public:
    DisplayManager(uint8_t cs, uint8_t dc, uint8_t rst);

    void begin();
    Adafruit_ILI9341& tft();

private:
    Adafruit_ILI9341 _tft;
};
