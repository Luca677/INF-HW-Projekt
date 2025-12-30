#include "PageController.h"

void PageController::add(PageID id, Page* page) {
    _pages[id] = page;
}

void PageController::set(PageID id) {
    _current = id;
}

void PageController::draw(Adafruit_ILI9341& tft) {
    _pages[_current]->draw(tft);
}

void PageController::touch(int x, int y, Adafruit_ILI9341& tft) {
    PageID next = _pages[_current]->handleTouch(x, y);
    if (next != _current) {
        _current = next;
        draw(tft);
        delay(200);
    }
}
