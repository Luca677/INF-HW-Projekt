#pragma once
#include "ui/Page.h"

class InfoPage : public Page {
public:
    void draw(Adafruit_ILI9341& tft) override;
    PageID handleTouch(
    int x,
    int y,
    Adafruit_ILI9341& tft,
    PageController& controller
) override;

};
