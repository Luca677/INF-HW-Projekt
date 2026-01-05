#pragma once
#include "ui/Page.h"
#include <vector>

// Zustandsenum das Farbauswahl-Overlay
enum class PaintOverlay {
    NONE,
    COLOR_PICKER
};

// PaintPage (Zeichenseite) Klasse, erbt von Page 
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
    // Allgemeine Zustandsattribute
    bool needsRedraw = true;
    PaintOverlay overlay = PaintOverlay::NONE;

    // Werkzeugzustandsattribute
    bool penActive = false;
    bool penDown = false;
    bool eraserActive = false;
    bool eraserDown = false;
    int brushsize = 4;
    uint16_t currentColor = ILI9341_BLACK;

    // Zeichenkoordinaten
    int lastX = 0, lastY = 0;
    int curX = 0, curY = 0;

    // Jeder Punkt ist ein (x,y) Paar
    struct Point {
        int x;
        int y;
    };

    // Ein Stroke (Strich) ist eine Sammlung von Punkten mit Farbe und Pinselgröße
    struct Stroke {
        std::vector<Point> points;
        uint16_t color;
        uint8_t brushsize;
    };   

    // Undo/Redo Stacks bestehen aus Strokes
    std::vector<Stroke> undoStack;
    std::vector<Stroke> redoStack;
    Stroke currentStroke;


    PageID handleColorPickerTouch(int x, int y);
};
