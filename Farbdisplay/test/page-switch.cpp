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


Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS);

// ------------------- Calibration (example) -------------------
int xMinVal = 200, xMaxVal = 3800;
int yMinVal = 200, yMaxVal = 3800;

// ------------------- Page Enum -------------------
enum Page { HOME, SETTINGS, INFO };
Page currentPage = HOME;

// ------------------- Button Defines -------------------
#define BTN_W 180
#define BTN_H 50

// ------------------- Drawing Functions -------------------
void drawHomePage() {
  tft.fillScreen(ILI9341_BLACK);

  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.print("Home Page");

  // Settings Button
  tft.fillRoundRect(70, 80, BTN_W, BTN_H, 8, ILI9341_BLUE);
  tft.setCursor(100, 98);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Settings");

  // Info Button
  tft.fillRoundRect(70, 150, BTN_W, BTN_H, 8, ILI9341_GREEN);
  tft.setCursor(130, 168);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Info");
}

void drawSettingsPage() {
  tft.fillScreen(ILI9341_DARKCYAN);

  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Settings");

  // Back Button
  tft.fillRoundRect(10, 200, 120, 40, 8, ILI9341_RED);
  tft.setCursor(40, 215);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Back");
}

void drawInfoPage() {
  tft.fillScreen(ILI9341_NAVY);

  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.print("Info Page");

  tft.setCursor(10, 60);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Version: 1.0");

  // Back Button
  tft.fillRoundRect(10, 200, 120, 40, 8, ILI9341_RED);
  tft.setCursor(40, 215);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Back");
}

// ------------------- Touch Helper -------------------
bool touchedIn(int x, int y, int w, int h, int tx, int ty) {
  return (tx > x && tx < x + w && ty > y && ty < y + h);
}

// ------------------- Setup -------------------
void setup() {
  tft.begin();
  ts.begin();

  tft.setRotation(1);
  ts.setRotation(3);

  drawHomePage();
}

// ------------------- Main Loop -------------------
void loop() {
  if (!ts.touched()){
    delay(10);
    return;
  } 

  TS_Point p = ts.getPoint();
  if (p.z < 200) return;

  int sx = map(p.x, xMinVal, xMaxVal, 0, 320);
  int sy = map(p.y, yMinVal, yMaxVal, 0, 240);

  // ------- PAGE HANDLING -------
  if (currentPage == HOME) {

    if (touchedIn(70, 80, BTN_W, BTN_H, sx, sy)) {   // Go to settings
      currentPage = SETTINGS;
      drawSettingsPage();
      delay(200);
    }

    if (touchedIn(70, 150, BTN_W, BTN_H, sx, sy)) {  // Go to info
      currentPage = INFO;
      drawInfoPage();
      delay(200);
    }
  }

  else if (currentPage == SETTINGS) {
    if (touchedIn(10, 200, 120, 40, sx, sy)) {       // Back
      currentPage = HOME;
      drawHomePage();
      delay(200);
    }
  }

  else if (currentPage == INFO) {
    if (touchedIn(10, 200, 120, 40, sx, sy)) {       // Back
      currentPage = HOME;
      drawHomePage();
      delay(200);
    }
  }
}