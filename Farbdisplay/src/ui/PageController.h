#pragma once
#include "Page.h"
#include <map>

class PageController {
public:
    void add(PageID id, Page* page);
    void set(PageID id);
    void draw(Adafruit_ILI9341& tft);
    void touch(int x, int y, Adafruit_ILI9341& tft);
    PageID getCurrentPage() const;
private:
    PageID _current;
    std::map<PageID, Page*> _pages;
    PageID _currentPage;
};
