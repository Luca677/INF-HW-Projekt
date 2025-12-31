#include "ui/SettingsPage.h"

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

void SettingsPage::draw(Adafruit_ILI9341& tft) {
    tft.fillScreen(ILI9341_DARKCYAN);

    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.print("Settings");

    // Back-Button
    tft.fillRoundRect(10, 190, 100, 40, 6, ILI9341_RED);
    tft.setCursor(30, 203);
    tft.setTextColor(ILI9341_WHITE);
    tft.print("Back");
}

PageID SettingsPage::handleTouch(int x, int y) {
    // Back Button
    if (inRect(10, 190, 100, 40, x, y))
        return PageID::HOME;

    return PageID::SETTINGS;
}
