#include "display/DisplayManager.h"
#include "touch/TouchManager.h"
#include "ui/PageController.h"
#include "ui/HomePage.h"
#include "ui/SettingsPage.h"
#include "ui/InfoPage.h"
#include "ui/PaintPage.h"

// GLOBALE OBJEKTE

// Kapselt das TFT-Display
DisplayManager display(PB6, PB7, PB8);

// Kapselt den Touchscreen
TouchManager touch(PB12, PA0);

// Verwaltet alle Seiten (Pages) und den Seitenwechsel
PageController pages;

// Konkrete Seitenobjekte
HomePage home;
SettingsPage settings;
InfoPage info;
PaintPage paint;

void setup() {
    Serial.begin(115200);

    // Initialisierung der Hardware
    display.begin();
    touch.begin();

    // Seiten registrieren beim PageController
    pages.add(PageID::HOME, &home);
    pages.add(PageID::SETTINGS, &settings);
    pages.add(PageID::INFO, &info);
    pages.add(PageID::PAINT, &paint);

    // Home-Seite als Startseite setzen 
    pages.set(PageID::HOME, display.tft());
    pages.draw(display.tft());
}

void loop() {
    // Touch auslesen
    auto p = touch.read();

    // Kein Touch erkannt
    if (!p.valid) {
        // Werkzeuge zurücksetzen, falls auf Paint-Seite
        if (pages.getCurrent() == PageID::PAINT) {
            paint.penUp();
            paint.eraserUp();
        }
        return;
    }

    // Touch an aktuelle Seite weiterleiten
    pages.touch(p.x, p.y, display.tft());

    // Seite neu zeichnen (falls nötig)
    pages.draw(display.tft());
}
