#include "DisplayManager.h"

DisplayManager::DisplayManager(uint8_t cs, uint8_t dc, uint8_t rst)
    : _tft(cs, dc, rst) {}

void DisplayManager::begin() {
    _tft.begin();
    _tft.setSPISpeed(40000000); // 40 MHz sonst 20MHz
    _tft.setRotation(1);
}

Adafruit_ILI9341& DisplayManager::tft() {
    return _tft;
}
