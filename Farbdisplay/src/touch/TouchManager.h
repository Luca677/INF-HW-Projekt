#pragma once
#include <XPT2046_Touchscreen.h>

/*
    TouchPoint ist ein einfaches Datenobjekt (Plain Old Data).

    Es enthält:
    - Koordinaten
    - ein Flag, ob der Touch gültig ist
*/
struct TouchPoint {
    int x;
    int y;
    bool valid;
};

/*
    TouchManager kapselt den Touchscreen.

    Vorteil:
    - Kalibrierung
    - Rohdaten
    - Mapping auf Displayauflösung
    sind vollständig ausgelagert
*/
class TouchManager {
public:
    TouchManager(uint8_t cs, uint8_t irq);

    void begin();
    TouchPoint read();

private:
    XPT2046_Touchscreen _ts;

    // Kalibrierungswerte
    int _xMin = 200;
    int _xMax = 3800;
    int _yMin = 200;
    int _yMax = 3800;
};
