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
        void eraserUp();
    private:
    //Stift aktivieren Variablen und Einstellungen
        bool penActive = false;
        bool penDown = false;
        int lastX = 0;
        int lastY = 0;
        int curX = 0;
        int curY = 0;
        int brushsize = 3; // auch für Radiergummi Größe
        //Radiergummi Variablen
        bool eraserActive = false;
        bool eraserDown = false;
};