#include "PaintPage.h"

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx > x && tx < x + w && ty > y && ty < y + h;
}
void PaintPage::draw(Adafruit_ILI9341& tft) {
    tft.fillScreen(ILI9341_WHITE);    
}

PageID PaintPage::handleTouch(int x, int y) {
    return PageID::PAINT;
}