#include "pantalla.h"
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define ORESET -1

Pantalla::Pantalla() {
  oled = NULL;
}

void Pantalla::begin() {
  Wire.begin();
  oled = new Adafruit_SSD1306(128, 64, &Wire, ORESET);

  if (!oled->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Failed to initialize SSD1306 display");
    while (1)
      ;
  }
  oled->display();
  delay(200);
  oled->clearDisplay();
  oled->drawPixel(10, 10, WHITE);
  oled->display();
  delay(200);
}

void Pantalla::clear() {
  if (oled != NULL) {
    oled->clearDisplay();
  }
}

void Pantalla::println(const char *text) {
  if (oled != NULL) {
    oled->setTextSize(2);
    oled->setTextColor(WHITE);
    oled->setCursor(0, 0);
    oled->println(text);
    oled->display();
  }
}