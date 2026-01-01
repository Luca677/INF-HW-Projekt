#include "PageController.h"

void PageController::add(PageID id, Page* page) {
    _pages[id] = page;
}

void PageController::set(PageID id) {
    _current = id;
    Serial.print("SET PAGE: ");
    Serial.println((int)id);

}

void PageController::draw(Adafruit_ILI9341& tft) {
    _pages[_current]->draw(tft);
}

PageID PageController::getCurrentPage() const {
    return _current;
}

void PageController::touch(int x, int y, Adafruit_ILI9341& tft) {
    PageID next = _pages[_current]->handleTouch(x, y, *this);
    if (next != _current) {
        _current = next;
        draw(tft);
        delay(200);
    }
}
