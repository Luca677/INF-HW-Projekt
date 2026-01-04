#pragma once
#include "ui/Page.h"
class SettingsPage : public Page {
    public:
        void onEnter() override;
        void draw(Adafruit_ILI9341& tft) override;
        PageID handleTouch(int x, int y,
            Adafruit_ILI9341& tft,
            PageController& controller) override;
    private:
        bool needsRedraw = true;
    };
