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

    pages.set(PageID::HOME, display.tft());
    pages.draw(display.tft());
}

void loop() {
    auto p = touch.read();

    // 👉 KEIN Touch
    if (!p.valid) {
        // ❗ Stift/Radierer nur loslassen,
        // ❗ wenn PaintPage wirklich aktiv ist
        if (pages.getCurrent() == PageID::PAINT) {
            paint.penUp();
            paint.eraserUp();
        }
        return;
    }

    // 👉 Touch an aktive Page weiterreichen
    pages.touch(p.x, p.y, display.tft());

    // 👉 Zeichnen der aktuellen Page
    pages.draw(display.tft());
}
