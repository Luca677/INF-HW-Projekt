#pragma once
#include <Adafruit_ILI9341.h>


//Jede Seite der Anwendung bekommt eine eindeutige ID.
enum class PageID {
    HOME,
    SETTINGS,
    INFO,
    PAINT,
    COUNT // Anzahl der Seiten (keine Seiten-ID)
};

class PageController;


//Abstrakte Oberklasse "Page"
class Page {
public:
    //Jede Klasse MUSS einen Destruktor haben
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
