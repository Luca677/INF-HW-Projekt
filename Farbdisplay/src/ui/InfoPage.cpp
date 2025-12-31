#include "ui/InfoPage.h"

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

void InfoPage::draw(Adafruit_ILI9341& tft) {
    tft.fillScreen(ILI9341_NAVY);

    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.print("Info");

    tft.setTextSize(1);
    tft.setCursor(10, 50);
    tft.print("STM32 Nucleo L152RE");
    tft.setCursor(10, 65);
    tft.print("Touch + TFT Demo");

    // Back-Button
    tft.fillRoundRect(10, 190, 100, 40, 6, ILI9341_RED);
    tft.setCursor(30, 203);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.print("Back");
}

PageID InfoPage::handleTouch(int x, int y) {
    if (inRect(10, 190, 100, 40, x, y))
        return PageID::HOME;

    return PageID::INFO;
}
