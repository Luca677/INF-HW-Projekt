#pragma once
#include "ui/Page.h"

class PaintPage : public Page {
    public:
        void draw(Adafruit_ILI9341& tft) override;
        PageID handleTouch(int x, int y) override;
};