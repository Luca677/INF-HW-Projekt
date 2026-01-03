#include "display/DisplayManager.h"
#include "touch/TouchManager.h"
#include "ui/PageController.h"
#include "ui/HomePage.h"
#include "ui/SettingsPage.h"
#include "ui/InfoPage.h"
#include "ui/PaintPage.h"

DisplayManager display(PB6, PB7, PB8);
TouchManager touch(PB12, PA0);
PageController pages;

HomePage home;
SettingsPage settings;
InfoPage info;
PaintPage paint;

void setup() {
    Serial.begin(115200);
    display.begin();
    touch.begin();

    pages.add(PageID::HOME, &home);
    pages.add(PageID::SETTINGS, &settings);
    pages.add(PageID::INFO, &info);
    pages.add(PageID::PAINT, &paint);

    pages.set(PageID::HOME);
    pages.draw(display.tft());
    paint.setTft(display.tft());
}

void loop() {
    auto p = touch.read();

    if(!p.valid) {
        paint.penUp();
        return;
    }

    Serial.print("CURRENT PAGE: ");
    Serial.println((int)pages.getCurrentPage());

    pages.touch(p.x, p.y, display.tft());
    pages.draw(display.tft());
}

//Pinbelegung TFT 2.8" ILI9341 mit Touch XPT2046 
// 1 3.3V 
// 2 GND 
// 3 TFT_CS PB6 
// 4 TFT_Reset PB8 
// 5 TFT_DC PB7 
// 6 MOSI PA7 
// 7 SCK PA5 
// 8 LED 3.3V 
// 9 MISO PA6 
// 10 T_CLK PA5 
// 11 T_CS PB12 
// 12 T_DIN PA7 
// 13 T_DO PA6 
// 14 T_IRQ PA0