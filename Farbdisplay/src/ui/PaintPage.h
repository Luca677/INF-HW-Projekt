#pragma once
#include "ui/Page.h"
class PageController;

enum class PaintOverlay {
    NONE,
    COLOR_PICKER
};

class PaintPage : public Page {
    public:
        PageID handleColorPickerTouch(int x, int y);
        void draw(Adafruit_ILI9341& tft) override;
        void onEnter() override;

        PageID handleTouch(
        int x,
        int y,
        Adafruit_ILI9341& tft,
        PageController& controller
        ) override;

        void penUp();
        void eraserUp();
        void onLeave() override;
        void setColor(uint16_t c);

    private:
        bool showFarbauswahl = false;
        bool needsRedraw = true;
        PaintOverlay overlay = PaintOverlay::NONE;
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
        uint16_t currentColor = ILI9341_BLACK;

};