#include "HomePage.h"
#include "assets/menu_bitmap.h"
#define BTN_W 180
#define BTN_H 50

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

void HomePage::draw(Adafruit_ILI9341& tft) {
    tft.drawRGBBitmap(0, 0, menuBitmap, MENU_W, MENU_H);
}

PageID HomePage::handleTouch(int x, int y) {
    // Settings Button (70,50,180,50) -> y=50..100
    if (inRect(70, 50, BTN_W, BTN_H, x, y))
        return PageID::SETTINGS;

    // Info Button (70,120,180,50) -> y=120..170
    if (inRect(70, 120, BTN_W, BTN_H, x, y))
        return PageID::INFO;
    if (inRect(80, 95, 160, 50, x, y)) {
        return PageID::PAINT;
    }
    return PageID::HOME;
}
