#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// ===== PIN-DEFINITION =====
#define TFT_CS   PB6
#define TFT_DC   PB7
#define TFT_RST  PB8

// ===== DISPLAY =====
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // SPI-PINS FEST setzen (EXTREM WICHTIG)
  SPI.setMOSI(PA7);
  SPI.setMISO(PA6);
  SPI.setSCK(PA5);

  SPI.begin();

  tft.begin();

  // Rotation korrekt setzen (verhindert schwarze Bereiche!)
  tft.setRotation(1); // 0..3 ausprobieren falls nötig

  // Bildschirm löschen
  tft.fillScreen(ILI9341_BLACK);

  // TEST: kompletter Screen ROT
  tft.fillScreen(ILI9341_RED);
}

void loop() {
}
