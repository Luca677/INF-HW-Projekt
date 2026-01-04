#pragma once
#include "ui/Page.h"
#include <vector>

class PageController;

enum class PaintOverlay {
    NONE,
    COLOR_PICKER
};

class PaintPage : public Page {
public:
    void draw(Adafruit_ILI9341& tft) override;
    PageID handleTouch(
        int x,
        int y,
        Adafruit_ILI9341& tft,
        PageController& controller
    ) override;

    void onEnter() override;
    void onLeave() override;

    void penUp();
    void eraserUp();
    void undo();
    void redo();

private:
    // UI / State
    bool needsRedraw = true;
    PaintOverlay overlay = PaintOverlay::NONE;

    // Tool state
    bool penActive = false;
    bool penDown = false;
    bool eraserActive = false;
    bool eraserDown = false;

    int lastX = 0;
    int lastY = 0;
    int curX  = 0;
    int curY  = 0;

    int brushsize = 3;
    uint16_t currentColor = ILI9341_BLACK;

    // ---------- Stroke Daten ----------
    struct Point {
        int x;
        int y;
    };

    struct Stroke {
        std::vector<Point> points;
        uint16_t color;
        uint8_t brushsize;   // ✅ FEHLENDES FELD
    };

    std::vector<Stroke> undoStack;
    std::vector<Stroke> redoStack;
    Stroke currentStroke;

    PageID handleColorPickerTouch(int x, int y);
};
