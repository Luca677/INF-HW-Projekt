#if 0
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

//Pinbelegung TFT 2.8" ILI9341 mit Touch XPT2046
// 1 3.3V
// 2 GND
// 3 TFT_CS PB6
// 4 TFT_Reset PB8
// 5 TFT_DC PB7
// 6 MOSI PA7
// 7 SCK PA5
// 8 LED 3.3V
// 9 MISO PA6
// 10 T_CLK PA5
// 11 T_CS PB12
// 12 T_DIN PA7
// 13 T_DO PA6
// 14 T_IRQ PA0

// Display
#define TFT_CS   PB6
#define TFT_DC   PB7
#define TFT_RST  PB8

// Touch
#define TOUCH_CS PB12
#define TOUCH_IRQ PA0

// Button-Definition
#define BTN_W 160
#define BTN_H 50
#define BTN1_X 40
#define BTN1_Y 80
#define BTN2_X 40
#define BTN2_Y 150

//Touchkalibrierung
int xMin = 300, xMax = 3800;
int yMin = 300, yMax = 3700;

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ); // nur CS + IRQ

// Buttons zeichnen
void drawButton() {
  tft.fillRect(BTN1_X, BTN1_Y, BTN_W, BTN_H, ILI9341_BLUE);
  tft.setCursor(BTN1_X + 20, BTN1_Y + 15);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Button 1");

  tft.fillRect(BTN2_X, BTN2_Y, BTN_W, BTN_H, ILI9341_RED);
  tft.setCursor(BTN2_X + 20, BTN2_Y + 15);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Button 2");
}

void setup() {
  Serial.begin(115200);

  // Display Pins
  pinMode(TFT_CS, OUTPUT);
  pinMode(TFT_DC, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(TFT_DC, HIGH);

  // Hardware SPI
  SPI.begin(); // STM32 nutzt automatisch PA5/PA6/PA7

  // Display starten
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);

  // Touch starten
  touch.begin();
  touch.setRotation(1);

  // Testtext
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(10, 10);
  tft.println("Touch Test");

  drawButton();
}

void loop() {
  if(touch.touched()) {
    TS_Point p = touch.getPoint();

    // Kalibrierung
    int X = map(p.x, xMin, xMax, 0, 320);
    int Y = map(p.y, yMin, yMax, 0, 240);

    X = constrain(X, 0, 319);
    Y = constrain(Y, 0, 239);

    X = 319 - X; // Spiegelung
    Y = 239 - Y;

    Serial.print("X = "); Serial.print(X);
    Serial.print("  Y = "); Serial.println(Y);

    // Prüfen, ob Touch über Buttons liegt
    bool overButton = false;
    if(X > BTN1_X && X < BTN1_X + BTN_W && Y > BTN1_Y && Y < BTN1_Y + BTN_H) {
      tft.fillRect(0, 0, 320, 20, ILI9341_BLACK);
      tft.setCursor(10, 10);
      tft.setTextColor(ILI9341_GREEN);
      tft.setTextSize(2);
      tft.println("Button 1 gedrueckt");
      overButton = true;
      delay(500);
    }
    if(X > BTN2_X && X < BTN2_X + BTN_W && Y > BTN2_Y && Y < BTN2_Y + BTN_H) {
      tft.fillRect(0, 0, 320, 20, ILI9341_BLACK);
      tft.setCursor(10, 10);
      tft.setTextColor(ILI9341_GREEN);
      tft.setTextSize(2);
      tft.println("Button 2 gedrueckt");
      overButton = true;
      delay(500);
    }

    // Zeichnen nur, wenn nicht über Buttons
    if(!overButton) {
      tft.fillCircle(X, Y, 3, ILI9341_YELLOW);
    }

    delay(5);
  }
}
#endif