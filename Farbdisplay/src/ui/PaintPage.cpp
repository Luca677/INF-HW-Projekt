#include "ui/PaintPage.h"
#include <math.h>
#define BTN_W 60
#define BTN_H 30

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

void drawColorWheel(Adafruit_ILI9341& tft)
{
    int radX = 50;
    int radY = 50;
    int radR = 40;
    for(int angle = 0; angle<360; angle++)
    {
        float rad = angle * PI /180.0;
        for(int r = 0; r<radR; r++)
        {
            int px = radX + r * cos(rad);
            int py = radY + r * sin(rad);
            // RGB-Farben
            uint8_t red = (uint8_t)(127.5*(1+cos(rad)));
            uint8_t green = (uint8_t)(127.5*(1+cos(rad - (2*PI/3))));
            uint8_t blue = (uint8_t)(127.5*(1+cos(rad - (4*PI/3))));
            tft.drawPixel(px, py , tft.color565(red, green, blue));

        }
    }
}

void PaintPage::draw(Adafruit_ILI9341& tft){
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(ILI9341_YELLOW);
    tft.setTextSize(1);
    tft.print("Zeichenflaeche");
    drawColorWheel(tft);
    // Back-Button
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
