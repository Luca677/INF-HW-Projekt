#include <Arduino.h>
#include <SPI.h>

#define cs PB0 // Chip Select An/Aus, Low = Display Aktiv 
#define rst PB1 // Reset Display, Low = Reset
#define dc PB2 // Data/Command, Low = Command, High = Data
#define led PB12 // Backlight An/Aus, High = An

#define sck PB3 // Serial Clock
#define miso PB4 // Master In Slave Out
#define mosi PB5 // Master Out Slave In

void writeCommand(uint8_t cmd) {
  digitalWrite(dc, LOW);
  digitalWrite(cs, LOW);
  SPI.transfer(cmd);
  digitalWrite(cs, HIGH);
}

void writeData(uint8_t data) {
  digitalWrite(dc, HIGH);
  digitalWrite(cs, LOW);
  SPI.transfer(data);
  digitalWrite(cs, HIGH);
}

void tftInit() {
  // Reset
  digitalWrite(rst, LOW);
  delay(50);
  digitalWrite(rst, HIGH);
  delay(120);

  // Sleep Out
  writeCommand(0x11);
  delay(120);

  // Display ON
  writeCommand(0x29);
}

void fillScreen(uint16_t color) {
  // Column Address Set
  writeCommand(0x2A);
  writeData(0 >> 8);
  writeData(0 & 0xFF);
  writeData((240 - 1) >> 8);
  writeData((240 - 1) & 0xFF);

  // Page Address Set
  writeCommand(0x2B);
  writeData(0 >> 8);
  writeData(0 & 0xFF);
  writeData((320 - 1) >> 8);
  writeData((320 - 1) & 0xFF);

  // RAM write
  writeCommand(0x2C);

  digitalWrite(dc, HIGH);
  digitalWrite(cs, LOW);
  for (int i = 0; i < 240 * 320; i++) {
    SPI.transfer(color >> 8);
    SPI.transfer(color & 0xFF);
  }
  digitalWrite(cs, HIGH);
}


void setup() {
  pinMode(cs, OUTPUT);
  pinMode(rst, OUTPUT);
  pinMode(dc, OUTPUT);
  pinMode(led, OUTPUT);

  digitalWrite(led, HIGH);

  // SPI starten
  SPI.begin();  // nutzt automatisch PA5/PA6/PA7

  tftInit(); // Display starten

    

}

void loop() {
  fillScreen(0xF800);// ROT anzeigen
}


