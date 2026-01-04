#pragma once
#include "Page.h"
#include <map>

/*
    PageController verwaltet:
    - alle Seiten
    - welche Seite aktuell aktiv ist
    - Seitenwechsel
*/
class PageController {
public:
    PageController() : _current(PageID::HOME) {}

    void add(PageID id, Page* page);
    void set(PageID id, Adafruit_ILI9341& tft);
    void draw(Adafruit_ILI9341& tft);
    void touch(int x, int y, Adafruit_ILI9341& tft);

    Page* get(PageID id);
    PageID getCurrent() const { return _current; }

private:
    PageID _current = PageID::HOME;
    std::map<PageID, Page*> _pages;
};
