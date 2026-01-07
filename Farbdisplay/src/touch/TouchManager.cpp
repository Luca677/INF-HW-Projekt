#include "TouchManager.h"

TouchManager::TouchManager(uint8_t cs, uint8_t irq)
    : _ts(cs, irq) {
}

void TouchManager::begin() {
    _ts.begin();
    _ts.setRotation(3);
}

TouchPoint TouchManager::read() {
    if (!_ts.touched())
        return {0, 0, false};

    TS_Point p = _ts.getPoint();

    // Druck zu gering --> kein echter Touch
    if (p.z < 200)
        return {0, 0, false};

    // A-D Wandlung mithilfe der map Funktion auf Display-Koordinaten umrechnen
    int x = map(p.x, _xMin, _xMax, 0, 320);
    int y = map(p.y, _yMin, _yMax, 0, 240);

    return {x, y, true};
}
