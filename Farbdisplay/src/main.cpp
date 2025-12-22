#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// ===== PIN-DEFINITION =====
#define TFT_CS   PB6  //Chip select signal
#define TFT_DC   PB7  // LCD Register /data selection signal
#define TFT_RST  PB8  // LCD reset signal

// ===== DISPLAY =====
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  SPI.setMISO(PA6);
  SPI.setMOSI(PA7);
  SPI.setSCLK(PA5);
  SPI.begin();

  tft.begin();

  // Rotation korrekt setzen
  tft.setRotation(1); // 0 bis 3 immer um 90 Grad gedreht = 0 Standard 1 = 90 Grad gedreht usw

  // Bildschirm löschen
  tft.fillScreen(ILI9341_BLACK);

  // TEST: kompletter Screen ROT
  tft.fillScreen(ILI9341_RED);
  // TEST: Ausgabe
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLUE);
  tft.print("Hello World");
}
void loop() {
  
}