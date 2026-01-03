#pragma once
#include "Page.h"

class HomePage : public Page {
public:
    void draw(Adafruit_ILI9341& tft) override;
    PageID handleTouch(
    int x,
    int y,
    Adafruit_ILI9341& tft,
    PageController& controller
) override;

};
