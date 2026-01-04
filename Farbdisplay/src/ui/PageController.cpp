#include "PageController.h"

void PageController::add(PageID id, Page* page) {
    _pages[id] = page;
}

void PageController::set(PageID id, Adafruit_ILI9341& tft) {
    if (id == _current)
        return;

    // Alte Seite verlassen
    _pages[_current]->onLeave();

    // Neue Seite aktivieren
    _current = id;
    _pages[_current]->onEnter();

    draw(tft);
}

Page* PageController::get(PageID id) {
    return _pages[id];
}

void PageController::draw(Adafruit_ILI9341& tft) {
    _pages[_current]->draw(tft);
}

void PageController::touch(int x, int y, Adafruit_ILI9341& tft) {
    if (_pages.find(_current) == _pages.end())
        return;

    PageID next = _pages[_current]->handleTouch(x, y, tft, *this);

    if (next != _current) {
        set(next, tft);
        delay(200); // Entprellung
    }
}
