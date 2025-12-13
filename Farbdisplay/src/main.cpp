#include <Arduino.h>
#define cs PB0; // Chip Select An/Aus, Low = Display Aktiv 
#define rst PB1; // Reset Display, Low = Reset
#define dc PB2;  // Data/Command, Low = Command, High = Data
#define led PB12; // Backlight An/Aus, High = An

#define sck PB3; // Serial Clock
#define miso PB4; // Master In Slave Out
#define mosi PB5; // Master Out Slave In

void setup() {
  pinMode(cs, OUTPUT); // Chip Select als Ausgang
  digitalWrite(cs, LOW); // Display aktivieren

  pinMode(rst, OUTPUT); // Reset als Ausgang
  digitalWrite(rst, LOW); // Display zurücksetzen
  delay(100); // Kurze Pause
  digitalWrite(rst, HIGH); // Display aus dem Reset holen

  pinMode(dc, OUTPUT); // Data/Command als Ausgang
  digitalWrite(dc, HIGH); // Auf Datenmodus setzen

  pinMode(led, OUTPUT); // Backlight als Ausgang
  digitalWrite(led, HIGH); // Backlight einschalten

  pinMode(sck, OUTPUT); // Serial Clock als Ausgang

  pinMode(miso, INPUT); // Master In Slave Out als Eingang
  
  pinMode(mosi, OUTPUT); // Master Out Slave In als Ausgang

}

void loop() {
  
}

