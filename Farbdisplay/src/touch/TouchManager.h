#pragma once
#include <XPT2046_Touchscreen.h>

// TouchPoint als einfache Datenklasse
struct TouchPoint {
    int x;
    int y;
    bool valid;
};

// TouchManager kapselt das XPT2046_Touchscreen Objekt
class TouchManager {
public:
    TouchManager(uint8_t cs, uint8_t irq);

    void begin();
    TouchPoint read();

private:
    XPT2046_Touchscreen _ts;

    // Analoge Extremwerte des Touchscreens
    int _xMin = 200;
    int _xMax = 3800;
    int _yMin = 200;
    int _yMax = 3800;
};
