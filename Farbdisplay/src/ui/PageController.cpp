#include "PageController.h"

void PageController::add(PageID id, Page* page) {
    _pages[id] = page;
}

void PageController::set(PageID id, Adafruit_ILI9341& tft) {
    if (id == _current) return;

    _pages[_current]->onLeave();   
    _current = id;
    _pages[_current]->onEnter();   

    draw(tft);
}


void PageController::draw(Adafruit_ILI9341& tft) {
    _pages[_current]->draw(tft);
}

PageID PageController::getCurrentPage() const {
    return _current;
}

void PageController::touch(int x, int y, Adafruit_ILI9341& tft) {
    PageID next = _pages[_current]->handleTouch(x, y, tft, *this);

    if (next != _current) {
        set(next, tft);   // ⭐ wichtig
        delay(200);
    }
}

