#include "ui/InfoPage.h"

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

void InfoPage::onEnter() {
    needsRedraw = true;   // 🔥 NUR BEIM BETRETEN
}

void InfoPage::draw(Adafruit_ILI9341& tft) {
    if (!needsRedraw) return;   // 🚨 DAS WAR DER FEHLER

    needsRedraw = false;

    tft.fillScreen(ILI9341_NAVY);

    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.print("Info");

    tft.setTextSize(1);
    tft.setCursor(10, 50);
    tft.print("Paint Programm auf ILI9341 Display");

    tft.setCursor(10, 65);
    tft.print("Winterprojekt von Luca Schreger und Henrik Wuertz");

    tft.setCursor(10, 80);
    tft.print("2025/26");

    tft.setCursor(10, 110);
    tft.print("Zeilen Code: ~800");
    tft.setCursor(10, 125);
    tft.print("Bitmaps: ~ 10500 Zeilen");

    tft.fillRoundRect(10, 190, 100, 40, 6, ILI9341_RED);
    tft.setCursor(30, 203);
    tft.setTextSize(2);
    tft.print("Back");
}

PageID InfoPage::handleTouch(
    int x, int y,
    Adafruit_ILI9341& tft,
    PageController& controller) {

    if (inRect(10, 190, 100, 40, x, y)) {
        return PageID::HOME;
    }

    return PageID::INFO;
}
