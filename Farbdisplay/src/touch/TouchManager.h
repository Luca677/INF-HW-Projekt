#pragma once
#include <XPT2046_Touchscreen.h>

struct TouchPoint {
    int x;
    int y;
    bool valid;
};

class TouchManager {
public:
    TouchManager(uint8_t cs, uint8_t irq);

    void begin();
    TouchPoint read();

private:
    XPT2046_Touchscreen _ts;
    int _xMin = 200, _xMax = 3800;
    int _yMin = 200, _yMax = 3800;
};
