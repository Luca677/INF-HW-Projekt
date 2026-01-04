#include "DisplayManager.h"

DisplayManager::DisplayManager(uint8_t cs, uint8_t dc, uint8_t rst)
    : _tft(cs, dc, rst) {
}

void DisplayManager::begin() {
    _tft.begin();

    // Maximale stabile SPI-Geschwindigkeit
    _tft.setSPISpeed(40000000);

    // Landscape-Modus
    _tft.setRotation(1);
}

Adafruit_ILI9341& DisplayManager::tft() {
    return _tft;
}
