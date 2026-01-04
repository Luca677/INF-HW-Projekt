#pragma once
#include <Adafruit_ILI9341.h>

/*
    Jede Seite der Anwendung bekommt eine eindeutige ID.
*/
enum class PageID {
    HOME,
    SETTINGS,
    INFO,
    PAINT,
    COUNT
};

class PageController;

/*
    Abstrakte Basisklasse "Page"

    - Definiert das gemeinsame Interface aller Seiten
    - Erzwingt konsistentes Verhalten
*/
class Page {
public:
    virtual ~Page() = default;

    // Jede Seite MUSS zeichnen können
    virtual void draw(Adafruit_ILI9341& tft) = 0;

    // Jede Seite MUSS Touch-Eingaben verarbeiten
    virtual PageID handleTouch(
        int x,
        int y,
        Adafruit_ILI9341& tft,
        PageController& controller
    ) = 0;

    // Optionaler Lebenszyklus
    virtual void onEnter() {}
    virtual void onLeave() {}
};
