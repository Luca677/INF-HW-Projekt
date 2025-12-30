#pragma once
#include <Adafruit_ILI9341.h>

enum class PageID { HOME, SETTINGS, INFO };

class Page {
public:
    virtual ~Page() = default;

    virtual void draw(Adafruit_ILI9341& tft) = 0;
    virtual PageID handleTouch(int x, int y) = 0;
};
