#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

//Pinbelegung TFT 2.8" ILI9341 mit Touch XPT2046
// 1          3.3V
// 2          GND
// 3   TFT_CS    PB6
// 4   TFT_Reset PB8
// 5   TFT_DC    PB7
// 6   MOSI      PA7
// 7   SCK       PA5
// 8   LED       3.3V
// 9   MISO      PA6
// 10  T_CLK     PA5
// 11  T_CS      PB12
// 12  T_DIN     PA7
// 13  T_DO      PA6
// 14  T_IRQ     PA0

// Display
#define TFT_CS   PB6
#define TFT_DC   PB7
#define TFT_RST  PB8

// Touch
#define TOUCH_CS PB12
#define TOUCH_IRQ PA0

#define BTN_W 160
#define BTN_H 50
#define BTN1_X 40
#define BTN1_Y 80
#define BTN2_X 40
#define BTN2_Y 150
//Touch
int xMin = 300;
int xMax = 3800;
int yMin = 300;
int yMax = 3700;

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ); // nur CS + IRQ

void drawButton()
{
  tft.fillRect(BTN1_X, BTN1_Y, BTN_W, BTN_H, ILI9341_BLUE);
  tft.setCursor(BTN1_X + 20, BTN1_Y + 15); // Cursor wird auf Position des Buttons gesetzt für Textausgabe (+15 und +20)
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Button 1");

  tft.fillRect(BTN2_X, BTN2_Y, BTN_W, BTN_H, ILI9341_RED);
  tft.setCursor(BTN2_X + 20, BTN2_Y + 15);// Cursor wird auf Position des Buttons gesetzt für Textausgabe (+15 und +20)
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Button 2");


}
void setup() {
  Serial.begin(115200);

  // Display-Pins
  pinMode(TFT_CS, OUTPUT);
  pinMode(TFT_DC, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(TFT_DC, HIGH);

  // Hardware SPI starten (SPI1)
  SPI.begin(); // benutzt PA5/PA6/PA7 automatisch auf STM32

  // Display starten
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);


  // Touch starten
  touch.begin();
  touch.setRotation(1);

  tft.setTextSize(2);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(10, 10);
  tft.println("Touch Test");
  drawButton();
}

void loop() {
  
  if (touch.touched()) {
    TS_Point p = touch.getPoint(); // roher Touchpunkt

    Serial.print("RAWX = "); Serial.print(p.x);
    Serial.print("  RAWY = "); Serial.println(p.y);

    // Kalibrierung
    int X = map(p.x, 300, 3800, 0, 320);
    int Y = map(p.y, 300, 3700, 0, 240);

    X = constrain(X, 0, 319);
    Y = constrain(Y, 0, 239);
    
    X = 319 - X; // Spiegeln X
    Y = 239 - Y; // Spiegeln Y
    Serial.print("X = "); Serial.print(X);
    Serial.print("  Y = "); Serial.println(Y);
    tft.fillCircle(X,Y, 3, ILI9341_YELLOW);
    if(X > BTN1_X && X< BTN1_X + BTN_W && Y > BTN1_Y && Y < BTN1_Y + BTN_H){
      tft.fillRect(0, 0, 320, 20, ILI9341_BLACK);
      tft.setCursor(10, 10);
      tft.setTextColor(ILI9341_GREEN);
      tft.print("Button 1 gedrueckt");
      delay(500);
    }
    if(X > BTN2_X && X< BTN2_X + BTN_W && Y > BTN2_Y && Y < BTN2_Y + BTN_H){
      tft.fillRect(0, 0, 320, 20, ILI9341_BLACK);
      tft.setCursor(10, 10);
      tft.setTextColor(ILI9341_GREEN);
      tft.print("Button 2 gedrueckt");
      delay(500);
    }
  }
  delay(5);
  
}