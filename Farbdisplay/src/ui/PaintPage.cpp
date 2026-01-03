#include "ui/PaintPage.h"
#include "assets/Paint_Bitmap.h"
#include "assets/Farbauswahl_Bitmap.h"
#include "ui/PageController.h"
#include <Adafruit_ILI9341.h>

// --------------------------------------------------
// Hilfsfunktion
// --------------------------------------------------
static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

// --------------------------------------------------
// Lebenszyklus
// --------------------------------------------------

void PaintPage::onEnter() {
    needsRedraw = true;
}

void PaintPage::onLeave() {
    penDown = false;
    eraserDown = false;
    penActive = false;
    eraserActive = false;
    overlay = PaintOverlay::NONE;
    needsRedraw = true;
}

// --------------------------------------------------
// Zeichnen
// --------------------------------------------------
void PaintPage::draw(Adafruit_ILI9341& tft) {

    // 1️⃣ Basis-UI einmal neu zeichnen
    if (needsRedraw) {
        tft.drawRGBBitmap(0, 0, paintBitmap, PAINT_W, PAINT_H);
        needsRedraw = false;
    }

    // 2️⃣ Overlay darüber (ohne Zeichenfläche zu löschen)
    if (overlay == PaintOverlay::COLOR_PICKER) {
        tft.drawRGBBitmap(
            18, 52,
            farbauswahlBitmap,
            FARBAUSWAHL_W,
            FARBAUSWAHL_H
        );
        return; // ⛔ darunter nichts verändern
    }

    // 3️⃣ Live-Zeichnen
    if (penActive && penDown) {
        tft.fillCircle(lastX, lastY, brushsize, currentColor);
        lastX = curX;
        lastY = curY;
    }

    if (eraserActive && eraserDown) {
        tft.fillCircle(lastX, lastY, brushsize, ILI9341_WHITE);
        lastX = curX;
        lastY = curY;
    }
}


// --------------------------------------------------
// Touch-Hilfen
// --------------------------------------------------
void PaintPage::penUp() {
    penDown = false;
}

void PaintPage::eraserUp() {
    eraserDown = false;
}

// --------------------------------------------------
// ColorPicker Touch
// --------------------------------------------------
PageID PaintPage::handleColorPickerTouch(int x, int y) {

    static const uint16_t colors[7] = {
        ILI9341_BLACK,
        ILI9341_RED,
        ILI9341_GREEN,
        ILI9341_BLUE,
        ILI9341_YELLOW,
        ILI9341_MAGENTA,
        ILI9341_CYAN
    };

    for (int i = 0; i < 7; i++) {
        if (inRect(18 + i * 42, 52, 40, 42, x, y)) {
            currentColor = colors[i];
            overlay = PaintOverlay::NONE;   // ✅ Overlay schließen
            needsRedraw = true;
            return PageID::PAINT;
        }
    }

    return PageID::PAINT;
}

// --------------------------------------------------
// Touch-Handling
// --------------------------------------------------
PageID PaintPage::handleTouch(int x, int y,
                              Adafruit_ILI9341& tft,
                              PageController& controller) {

    // 🎨 Overlay aktiv → NUR ColorPicker
    if (overlay == PaintOverlay::COLOR_PICKER) {
        return handleColorPickerTouch(x, y);
    }

    // 1️⃣ Stift
    if (inRect(18, 4, 40, 42, x, y)) {
        penActive = true;
        eraserActive = false;
        penDown = false;
        overlay = PaintOverlay::COLOR_PICKER;
        needsRedraw = true;
        return PageID::PAINT;
    }

    // 2️⃣ Radierer
    if (inRect(60, 4, 38, 42, x, y)) {
        eraserActive = true;
        penActive = false;
        eraserDown = false;
        return PageID::PAINT;
    }

    // 3️⃣–5️⃣ Pinselgrößen
    if (inRect(102, 4, 36, 42, x, y)) { brushsize = 6; return PageID::PAINT; }
    if (inRect(142, 4, 36, 42, x, y)) { brushsize = 4; return PageID::PAINT; }
    if (inRect(184, 4, 34, 42, x, y)) { brushsize = 2; return PageID::PAINT; }

    // 8️⃣ Hauptmenü
    if (inRect(0, 78, 14, 134, x, y)) {
        onLeave();
        return PageID::HOME;
    }

    // 9️⃣ Zeichenfläche
    if (inRect(18, 52, 282, 182, x, y)) {

        if (penActive) {
            eraserActive = false;
            if (!penDown) {
                penDown = true;
                lastX = curX = x;
                lastY = curY = y;
            } else {
                curX = x;
                curY = y;
            }
        }

        if (eraserActive) {
            penActive = false;
            if (!eraserDown) {
                eraserDown = true;
                lastX = curX = x;
                lastY = curY = y;
            } else {
                curX = x;
                curY = y;
            }
        }
    }

    // 🔟 Löschen (nur UI neu zeichnen)
    if (inRect(302, 74, 16, 134, x, y)) {
        needsRedraw = true;
    }

    return PageID::PAINT;
}
