void Lib1::drawHomePage() {
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