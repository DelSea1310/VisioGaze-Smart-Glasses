#ifndef PANTALLA_H
#define PANTALLA_H

#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

class Pantalla {
private:
  Adafruit_SSD1306 *oled;

public:
  Pantalla();
  void begin();
  void clear();
  void println(const char *text);
};

#endif