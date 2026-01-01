#include "ui/PaintPage.h"
#include "assets/Paint_Bitmap.h"
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
//9 Button Fläche 18-52 & 300-234 (y noch unten und oben erhöhen!)
//10 Button Löschen 302-74 & 318 208 (y noch unten und oben erhöhen!)

static bool inRect(int x, int y, int w, int h, int tx, int ty) {
    return tx >= x && tx < x + w && ty >= y && ty < y + h;
}

void PaintPage::draw(Adafruit_ILI9341& tft){
   tft.drawRGBBitmap(0, 0, paintBitmap, PAINT_W, PAINT_H); 
}

// 1 Button Stift (18-4) -> (58-46)
PageID PaintPage::handleTouch(int x, int y, PageController& controller) {
    Serial.print("PaintPage::handleTouch");
    Serial.print(x);
    Serial.print(" , ");
    Serial.println(y);

    if (controller.getCurrentPage() != PageID::PAINT) {
        return PageID::PAINT;
    }
    if (inRect(18, 4, 40, 42, x, y)) { // Stift 
        /* return ... */;
    }
    // 2 Button Radiergummi (60-4) -> (98-46)
    if (inRect(60, 4, 38, 42, x, y)) { // Radiergummi
        /* return ... */;
    }
    // 3 Button Groß (102-4) -> (138-46)    
    if (inRect(102, 4, 36, 42, x, y)) { // Groß
        /* return ... */;
    }
    // 4 Button Mittel (142-4) -> (178-46)

    if (inRect(142, 4, 36, 42, x, y)) { // Mittel
        /* return ... */;
    }
    // 5 Button Klein (184-4) -> (218-46)

    if (inRect(184, 4, 34, 42, x, y)) { // Klein
        /* return ... */;
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
        Serial.println("Hauptmenü gedrückt");
        return PageID::HOME;
    }
    // 9 Button Fläche (18-52) -> (300-234)

    // Hinweis: y oben/unten ggf. noch vergrößern
    if (inRect(18, 52, 282, 182, x, y)) { // Fläche
        /* return ... */;
    }
    // 10 Button Löschen (302-74) -> (318-208)

    // Hinweis: y oben/unten ggf. noch vergrößern
    if (inRect(302, 74, 16, 134, x, y)) { // Löschen
        /* return ... */;
    }

    return PageID::PAINT;
}
