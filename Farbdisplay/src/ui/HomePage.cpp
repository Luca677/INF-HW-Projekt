#include "HomePage.h"

#define BTN_W 180
#define BTN_H 50

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx > x && tx < x + w && ty > y && ty < y + h;
}

void HomePage::draw(Adafruit_ILI9341& tft) {
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_YELLOW);
    tft.setTextSize(2);
    tft.print("Home Page");

    tft.fillRoundRect(70, 80, BTN_W, BTN_H, 8, ILI9341_BLUE);
    tft.setCursor(100, 98);
    tft.setTextColor(ILI9341_WHITE);
    tft.print("Settings");

    tft.fillRoundRect(70, 150, BTN_W, BTN_H, 8, ILI9341_GREEN);
    tft.setCursor(130, 168);
    tft.print("Info");
}

PageID HomePage::handleTouch(int x, int y) {
    if (inRect(70, 80, BTN_W, BTN_H, x, y))
        return PageID::SETTINGS;

    if (inRect(70, 150, BTN_W, BTN_H, x, y))
        return PageID::INFO;

    return PageID::HOME;
}
