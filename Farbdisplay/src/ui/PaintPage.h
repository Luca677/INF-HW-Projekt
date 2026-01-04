#pragma once
#include "ui/Page.h"
#include <vector>

/*
 * PaintOverlay
 * ------------
 * Zustand der PaintPage-Oberfläche.
 * Wird verwendet, um Overlays sauber vom Zeichenbereich zu trennen.
 */
enum class PaintOverlay {
    NONE,
    COLOR_PICKER
};

/*
 * PaintPage
 * ---------
 * Konkrete Implementierung einer Page.
 *
 * Vererbt von Page und überschreibt draw(), handleTouch(),
 * onEnter() und onLeave().
 */
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

    void undo();
    void redo();

    void penUp();
    void eraserUp();

private:
    // ---------------- Zustandsverwaltung ----------------
    bool needsRedraw = true;
    PaintOverlay overlay = PaintOverlay::NONE;

    // ---------------- Werkzeug-Zustand ----------------
    bool penActive = false;
    bool penDown = false;
    bool eraserActive = false;
    bool eraserDown = false;

    int lastX = 0, lastY = 0;
    int curX = 0, curY = 0;

    int brushsize = 3;
    uint16_t currentColor = ILI9341_BLACK;

    // ---------------- Undo / Redo ----------------
    /*
     * Jeder Strich wird als Objekt gespeichert.
     * Das ist echtes objektorientiertes Denken:
     * Ein Strich ist ein eigenes Datenobjekt.
     */
    struct Point {
        int x;
        int y;
    };

    struct Stroke {
        std::vector<Point> points;
        uint16_t color;
        uint8_t brushsize;
    };

    std::vector<Stroke> undoStack;
    std::vector<Stroke> redoStack;
    Stroke currentStroke;

    // Interne Hilfsfunktion
    PageID handleColorPickerTouch(int x, int y);
};
