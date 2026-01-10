#include "ui/PaintPage.h"
#include "assets/Paint_Bitmap.h"
#include "assets/Farbauswahl_Bitmap.h"
#include "ui/PageController.h"
#include <Adafruit_ILI9341.h>
#include <algorithm>

// --------------------------------------------------
// Hilfsfunktion
// --------------------------------------------------
static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

// --------------------------------------------------
// Lifecycle
// --------------------------------------------------
void PaintPage::onEnter() {
    needsRedraw = true;
    Serial.println("Entering PaintPage");
}

void PaintPage::onLeave() {
    penDown = false;
    eraserDown = false;
    penActive = false;
    eraserActive = false;
    overlay = PaintOverlay::NONE;
    needsRedraw = true;
    Serial.println("Leaving PaintPage");
}

// --------------------------------------------------
// Drawing
// --------------------------------------------------
void PaintPage::draw(Adafruit_ILI9341& tft) {
    Serial.println("Needs Redraw: " + String(needsRedraw));
    // UI + alle gespeicherten Striche
    if (needsRedraw) {
        tft.drawRGBBitmap(0, 0, paintBitmap, PAINT_W, PAINT_H);

        for (const auto& stroke : undoStack) {
            for (size_t i = 1; i < stroke.points.size(); i++) {
                int x0 = stroke.points[i - 1].x;
                int y0 = stroke.points[i - 1].y;
                int x1 = stroke.points[i].x;
                int y1 = stroke.points[i].y;

                int dx = x1 - x0;
                int dy = y1 - y0;
                int steps = std::max(abs(dx), abs(dy));

                for (int s = 0; s <= steps; s++) {
                    int px = x0 + dx * s / steps;
                    int py = y0 + dy * s / steps;
                    tft.fillCircle(px, py, stroke.brushsize, stroke.color);
                }
            }
        }

        needsRedraw = false;
    }

    //  ColorPicker Overlay
    if (overlay == PaintOverlay::COLOR_PICKER) {
        tft.drawRGBBitmap(
            18, 52,
            farbauswahlBitmap,
            FARBAUSWAHL_W,
            FARBAUSWAHL_H
        );
        Serial.println("Drawing Color Picker Overlay");
        return;
    }

    // Live-Zeichnen
    if (penDown || eraserDown) {
        uint16_t color = penActive ? currentColor : ILI9341_WHITE;

        int dx = curX - lastX;
        int dy = curY - lastY;
        int steps = std::max(abs(dx), abs(dy));

        for (int s = 0; s <= steps; s++) {
            int px = lastX + dx * s / steps;
            int py = lastY + dy * s / steps;
            tft.fillCircle(px, py, brushsize, color);
            currentStroke.points.push_back({px, py});
        }

        Serial.println("Drawing Live Stroke");

        lastX = curX;
        lastY = curY;
    }
}

// --------------------------------------------------
// Touch helpers
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

// --------------------------------------------------
// Undo / Redo
// --------------------------------------------------
void PaintPage::undo() {
    if (undoStack.empty()) return;
    redoStack.push_back(undoStack.back());
    undoStack.pop_back();
    needsRedraw = true;
    Serial.println("Undo Action");
}

void PaintPage::redo() {
    if (redoStack.empty()) return;
    undoStack.push_back(redoStack.back());
    redoStack.pop_back();
    needsRedraw = true;
    Serial.println("Redo Action");
}

// --------------------------------------------------
// ColorPicker
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
            overlay = PaintOverlay::NONE;
            penDown = false;
            eraserDown = false;
            needsRedraw = true;
            return PageID::PAINT;
            Serial.print("Selected Color: " + String(colors[i]));
        }
    }
    Serial.println("Color Picker Touch Outside");
    return PageID::PAINT;
}

// --------------------------------------------------
// Touch handling
// --------------------------------------------------
PageID PaintPage::handleTouch(int x, int y,
                              Adafruit_ILI9341& tft,
                              PageController& controller) {

    // Overlay aktiv
    if (overlay == PaintOverlay::COLOR_PICKER) {
        return handleColorPickerTouch(x, y);
        Serial.println("Handling Color Picker Touch");
    }

    // Stift
    if (inRect(18, 4, 40, 42, x, y)) {
        penActive = true;
        eraserActive = false;
        overlay = PaintOverlay::COLOR_PICKER;
        return PageID::PAINT;
        Serial.println("Activating Color Picker Overlay");
    }

    // Radierer
    if (inRect(60, 4, 38, 42, x, y)) {
        eraserActive = true;
        penActive = false;
        return PageID::PAINT;
        Serial.println("Eraser Activated");
    }

    // Brushsize
    if (inRect(102, 4, 36, 42, x, y)) { brushsize = 6; return PageID::PAINT; Serial.println("Brushsize set to 6"); }
    if (inRect(142, 4, 36, 42, x, y)) { brushsize = 4; return PageID::PAINT; Serial.println("Brushsize set to 4");}
    if (inRect(184, 4, 34, 42, x, y)) { brushsize = 2; return PageID::PAINT; Serial.println("Brushsize set to 2");}

    // Undo / Redo
    if (inRect(226, 4, 22, 42, x, y)) { undo(); return PageID::PAINT; }
    if (inRect(268, 4, 20, 42, x, y)) { redo(); return PageID::PAINT; }

    // Löschen
    if (inRect(302, 74, 16, 134, x, y)) {
        undoStack.clear();
        redoStack.clear();
        currentStroke.points.clear();
        penDown = false;
        eraserDown = false;
        needsRedraw = true;
        return PageID::PAINT;
        Serial.println("Canvas Cleared");
    }

    // Hauptmenü
    if (inRect(0, 78, 14, 134, x, y)) {
        onLeave();
        return PageID::HOME;
        Serial.println("Returning to Home Page");
    }

    // Zeichenfläche
    if (inRect(24, 58, 272, 172, x, y)) {
        if (!(penDown || eraserDown)) {
            currentStroke.points.clear();
            currentStroke.color = penActive ? currentColor : ILI9341_WHITE;
            currentStroke.brushsize = brushsize;

            penDown = penActive;
            eraserDown = eraserActive;

            lastX = curX = x;
            lastY = curY = y;

            currentStroke.points.push_back({x, y});
            Serial.println("Starting New Stroke");
        } else {
            curX = x;
            curY = y;
        }
    }

    return PageID::PAINT;
}
