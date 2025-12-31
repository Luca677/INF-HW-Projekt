#include "ui/PaintPage.h"
#define BTN_W 60
#define BTN_H 30

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

void PaintPage::draw(Adafruit_ILI9341& tft){
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_YELLOW);
    tft.setTextSize(3);
    tft.print("Zeichenflaeche");

    tft.fillRoundRect(10, 190, 100, 40, 6, ILI9341_RED);
    tft.setCursor(30, 203);
    tft.setTextColor(ILI9341_WHITE);
    tft.print("Back");
}

PageID PaintPage::handleTouch(int x, int y) {
    if (inRect(10, 190, 100, 40, x, y))
        return PageID::HOME;

    return PageID::PAINT;
}
