#include "ui/PaintPage.h"
#include "assets/Paint_Bitmap.h"
#include "assets/Farbauswahl_Bitmap.h"
#include "ui/PageController.h"
#include <Adafruit_ILI9341.h>
#include <math.h>
#define BTN_W 60
#define BTN_H 30

//BUTTONS
//1 Button Stift 18-4 & 58-46
//2 Button Radiergummi 60-4 & 98-46
//3 Button Groß 102-4 & 138-46
//4 Button Mittel 142-4 & 178-46
//5 Button Klein 184-4 & 218-46
//6 Button Undo 226-4 & 248-46
//7 Button Redo 268-4 & 288-46
//8 Button Hauptmenü 0-78 & 14-212
//9 ZeichenFläche 18-52 & 300-234 (y noch unten und oben erhöhen!)
//10 Button Löschen 302-74 & 318 208 (y noch unten und oben erhöhen!)



static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}



void PaintPage::onLeave() {
    penDown = false;
    eraserDown = false;
    penActive = false;
    eraserActive = false;

    showFarbauswahl = false;
    needsRedraw = true;

    Serial.println("PaintPage verlassen → Zustand zurückgesetzt");
}


void PaintPage::draw(Adafruit_ILI9341& tft) {
    if (needsRedraw) {
        tft.drawRGBBitmap(0, 0, paintBitmap, PAINT_W, PAINT_H);

        if (showFarbauswahl) {
            tft.drawRGBBitmap(18, 52,
                              farbauswahlBitmap,
                              FARBAUSWAHL_W,
                              FARBAUSWAHL_H);
        }

        needsRedraw = false;
    }

    // Live-Zeichnen
    if (penActive && penDown) {
        tft.fillCircle(lastX, lastY, brushsize, ILI9341_BLACK);
        lastX = curX;
        lastY = curY;
    }

    if (eraserActive && eraserDown) {
        tft.fillCircle(lastX, lastY, brushsize, ILI9341_WHITE);
        lastX = curX;
        lastY = curY;
    }
}

void PaintPage::penUp(){
    penDown = false;
}
void PaintPage::eraserUp(){
    eraserDown = false;
}
// 1 Button Stift (18-4) -> (58-46)
PageID PaintPage::handleTouch(int x, int y,Adafruit_ILI9341& tft, PageController& controller) {
    Serial.print("PaintPage::handleTouch");
    Serial.print(x);
    Serial.print(" , ");
    Serial.println(y);

    if (inRect(18, 4, 40, 42, x, y)) { // Stift 
        penActive = true;
        eraserActive = false;
        penDown = false;

        showFarbauswahl = true;
        needsRedraw = true;

        return PageID::PAINT;
    }
    // 2 Button Radiergummi (60-4) -> (98-46)
    if (inRect(60, 4, 38, 42, x, y)) { // Radiergummi
        /* return ... */;
        eraserActive = true;
        penActive = false;
        eraserDown = false;
        Serial.println("Radiergummi aktiviert");
        return PageID::PAINT;
    }
    // 3 Button Groß (102-4) -> (138-46)    
    if (inRect(102, 4, 36, 42, x, y)) { // Groß
        /* return ... */;
        brushsize = 6;
        Serial.println("Pinselgröße Groß gewählt");
        return PageID::PAINT;
    }
    // 4 Button Mittel (142-4) -> (178-46)

    if (inRect(142, 4, 36, 42, x, y)) { // Mittel
        /* return ... */;
        brushsize = 4;
        Serial.println("Pinselgröße Mittel gewählt");
        return PageID::PAINT;
    }
    // 5 Button Klein (184-4) -> (218-46)

    if (inRect(184, 4, 34, 42, x, y)) { // Klein
        /* return ... */;
        brushsize = 2;
        Serial.println("Pinselgröße Klein gewählt");
        return PageID::PAINT;
    }
    // 6 Button Undo (226-4) -> (248-46)

    if (inRect(226, 4, 22, 42, x, y)) { // Undo
        /* return ... */;
    }
    // 7 Button Redo (268-4) -> (288-46)

    if (inRect(268, 4, 20, 42, x, y)) { // Redo
        /* return ... */;
    }
    // 8 Button Hauptmenü (0-78) -> (14-212)

    if (inRect(0, 78, 14, 134, x, y)) { // Hauptmenü
        eraserActive = false;
        penActive = false;
        Serial.println("Hauptmenü gedrückt");
        return PageID::HOME;
        onLeave();
    }
    // 9 ZeichenFläche (18-52) -> (300-234)

    // Hinweis: y oben/unten ggf. noch vergrößern
    if (inRect(18, 52, 282, 182, x, y)) { // Fläche
        /* return ... */;
        if(penActive)
        {
            eraserActive = false;
            if(!penDown)
            {
                penDown = true;
                curX = x;
                curY = y;
                lastX = curX;
                lastY = curY;
            }
            else{
                curX = x;
                curY = y;
            }

        }
        if(eraserActive)
        {
            penActive = false;
            if(!eraserDown)
            {
                eraserDown = true;
                curX = x;
                curY = y;
                lastX = curX;
                lastY = curY;
            }
            else
            {
              curX = x;
              curY = y;  
            }
        }
    }
    // 10 Button Löschen (302-74) -> (318-208)

    // Hinweis: y oben/unten ggf. noch vergrößern
    if (inRect(302, 74, 16, 134, x, y)) { // Löschen
        needsRedraw = true;
    }

    return PageID::PAINT;
}
