#pragma once
#include "ui/Page.h"
class PageController;
class PaintPage : public Page {
    public:
        void draw(Adafruit_ILI9341& tft) override;
        void drawFarbauswahl(Adafruit_ILI9341& tft);
        void setTft(Adafruit_ILI9341& tft);
        PageID handleTouch(int x, int y, PageController& controller) override;
        void penUp();
    private:
        bool penActive = false;
        bool penDown = false;
        int lastX = 0;
        int lastY = 0;
        int curX = 0;
        int curY = 0;
        int r = 3;
};