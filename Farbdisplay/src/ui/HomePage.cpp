#include "HomePage.h"
#include "assets/menu_bitmap.h"
#define BTN_W 158
#define BTN_H 64

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

void HomePage::draw(Adafruit_ILI9341& tft) {
    tft.drawRGBBitmap(0, 0, menuBitmap, MENU_W, MENU_H);
}

PageID HomePage::handleTouch(int x, int y) {
    //
    if (inRect(0, 62, BTN_W, BTN_H, x, y)) {
        return PageID::PAINT;
    }
    // Settings Button (70,50,180,50) -> y=50..100
    if (inRect(160, 100, BTN_W, BTN_H, x, y))
        return PageID::SETTINGS;

    // Info Button (70,120,180,50) -> y=120..170
    if (inRect(0, 140, BTN_W, BTN_H, x, y))
        return PageID::INFO;
    
    return PageID::HOME;
}
