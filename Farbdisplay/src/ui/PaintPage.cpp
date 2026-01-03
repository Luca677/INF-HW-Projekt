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
        // Hintergrundbitmap
        tft.drawRGBBitmap(0, 0, paintBitmap, PAINT_W, PAINT_H);

        // Alle Striche aus UndoStack zeichnen
        for (const auto& stroke : undoStack) {
            for (size_t i = 1; i < stroke.points.size(); i++) {
                int x0 = stroke.points[i-1].x;
                int y0 = stroke.points[i-1].y;
                int x1 = stroke.points[i].x;
                int y1 = stroke.points[i].y;

                int dx = x1 - x0;
                int dy = y1 - y0;
                int steps = max(abs(dx), abs(dy));

                for (int s = 0; s <= steps; s++) {
                    int px = x0 + dx * s / steps;
                    int py = y0 + dy * s / steps;
                    tft.fillCircle(px, py, stroke.brushsize, stroke.color);
                }
            }
        }

        // Farbauswahl
        if (showFarbauswahl) {
            tft.drawRGBBitmap(18, 52, farbauswahlBitmap, FARBAUSWAHL_W, FARBAUSWAHL_H);
        }

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
    // Live-Zeichnen während Touch
    if (penDown || eraserDown) {
        uint16_t color = penActive ? ILI9341_BLACK : ILI9341_WHITE;

        int dx = curX - lastX;
        int dy = curY - lastY;
        int steps = max(abs(dx), abs(dy));

        for (int s = 0; s <= steps; s++) {
            int px = lastX + dx * s / steps;
            int py = lastY + dy * s / steps;
            tft.fillCircle(px, py, brushsize, color);
            currentStroke.points.push_back({px, py});
        }

        lastX = curX;
        lastY = curY;
    }
}


// --------------------------------------------------
// Touch-Hilfen
// --------------------------------------------------

void PaintPage::penUp() {
    if (penDown && !currentStroke.points.empty()) {
        undoStack.push_back(currentStroke);
        redoStack.clear();
        currentStroke.points.clear();
    }
    penDown = false;
}

void PaintPage::eraserUp() {
    if (eraserDown && !currentStroke.points.empty()) {
        undoStack.push_back(currentStroke);
        redoStack.clear();
        currentStroke.points.clear();
    }
    eraserDown = false;
}

void PaintPage::undo() {
    if (undoStack.empty()) return;

    redoStack.push_back(undoStack.back());
    undoStack.pop_back();

    penDown = false;
    eraserDown = false;
    needsRedraw = true;
}

void PaintPage::redo() {
    if (redoStack.empty()) return;

    undoStack.push_back(redoStack.back());
    redoStack.pop_back();

    penDown = false;
    eraserDown = false;
    needsRedraw = true;
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
    // 9 ZeichenFläche (18-52) -> (300-234)

    // Hinweis: y oben/unten ggf. noch vergrößern
    if (inRect(18, 52, 282, 182, x, y)) { // Fläche
        /* return ... */;
        if (penActive || eraserActive) {
            if (!(penDown || eraserDown)) {
                currentStroke.points.clear();
                currentStroke.color = penActive ? ILI9341_BLACK : ILI9341_WHITE;
                currentStroke.brushsize = brushsize;
        
                penDown = penActive;
                eraserDown = eraserActive;
        
                curX = x;
                curY = y;
                lastX = x;
                lastY = y;
        
                currentStroke.points.push_back({x, y});
            } else {
                curX = x;
                curY = y;
            }
        }

        
    }
    return PageID::PAINT;
    

    // 10 Button Löschen (302-74) -> (318-208)

    // Hinweis: y oben/unten ggf. noch vergrößern
    if (inRect(302, 74, 16, 134, x, y)) { // Löschen
        undoStack.clear();
        redoStack.clear();
        needsRedraw = true;
    }

    return PageID::PAINT;
}
