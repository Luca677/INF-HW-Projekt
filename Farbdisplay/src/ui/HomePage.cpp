#include "HomePage.h"

#define BTN_W 180
#define BTN_H 50

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

void HomePage::draw(Adafruit_ILI9341& tft) {
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_YELLOW);
    tft.setTextSize(2);
    tft.print("Home Page");

    tft.fillRoundRect(70, 50, BTN_W, BTN_H, 8, ILI9341_BLUE);
    tft.setCursor(100, 68);
    tft.setTextColor(ILI9341_WHITE);
    tft.print("Settings");

    tft.fillRoundRect(70, 120, BTN_W, BTN_H, 8, ILI9341_GREEN);
    tft.setCursor(130, 138);
    tft.print("Info");

    tft.fillRoundRect(70, 180, BTN_W, BTN_H, 8, ILI9341_ORANGE);
    tft.setCursor(100, 198);
    tft.print("Drawing");
}

PageID HomePage::handleTouch(int x, int y) {
    // Settings Button (70,50,180,50) -> y=50..100
    if (inRect(70, 50, BTN_W, BTN_H, x, y))
        return PageID::SETTINGS;

    // Info Button (70,120,180,50) -> y=120..170
    if (inRect(70, 120, BTN_W, BTN_H, x, y))
        return PageID::INFO;

    // Drawing Button (70,190,180,50) -> y=190..240
    if (inRect(70, 190, BTN_W, BTN_H, x, y))
        return PageID::DRAWING;

    return PageID::HOME;
}
