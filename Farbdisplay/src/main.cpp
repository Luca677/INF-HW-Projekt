#include "display/DisplayManager.h"
#include "touch/TouchManager.h"
#include "ui/PageController.h"
#include "ui/HomePage.h"
#include "ui/SettingsPage.h"
#include "ui/InfoPage.h"

DisplayManager display(PB6, PB7, PB8);
TouchManager touch(PB12, PA0);
PageController pages;

HomePage home;
SettingsPage settings;
InfoPage info;

void setup() {
    display.begin();
    touch.begin();

    pages.add(PageID::HOME, &home);
    pages.add(PageID::SETTINGS, &settings);
    pages.add(PageID::INFO, &info);

    pages.set(PageID::HOME);
    pages.draw(display.tft());
}

void loop() {
    auto p = touch.read();
    if (!p.valid) return;

    pages.touch(p.x, p.y, display.tft());
}
