#include "display/DisplayManager.h"
#include "touch/TouchManager.h"
#include "ui/PageController.h"
#include "ui/HomePage.h"
#include "ui/SettingsPage.h"
#include "ui/InfoPage.h"
#include "ui/PaintPage.h"

/*
 * Globale Objekte
 * ----------------
 * Diese Objekte existieren während der gesamten Laufzeit des Programms.
 * Sie repräsentieren die zentralen Systemkomponenten.
 */

// Kapselt das TFT-Display (Hardware-Abstraktion)
DisplayManager display(PB6, PB7, PB8);

// Kapselt den Touchscreen (Hardware-Abstraktion)
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

    /*
     * Registrierung der Seiten beim PageController
     * ---------------------------------------------
     * Der PageController speichert nur Zeiger auf Page-Objekte.
     * Dadurch kann er polymorph arbeiten (virtuelle Funktionen).
     */
    pages.add(PageID::HOME, &home);
    pages.add(PageID::SETTINGS, &settings);
    pages.add(PageID::INFO, &info);
    pages.add(PageID::PAINT, &paint);

    // Startseite setzen
    pages.set(PageID::HOME, display.tft());
    pages.draw(display.tft());
}

void loop() {
    // Touch auslesen
    auto p = touch.read();

    // Kein Touch erkannt
    if (!p.valid) {
        /*
         * Sonderfall PaintPage:
         * Wenn der Finger losgelassen wird, muss ein aktiver Strich
         * sauber abgeschlossen werden (Undo/Redo funktioniert sonst nicht).
         */
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
