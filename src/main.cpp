#include <Arduino.h>

#include "display.h"

#include <U8g2lib.h>

Display display;

void setup()
{
  Serial.begin(9600);
  delay(1000);

  Serial.println("init()");
  display.init();

  Serial.println("draw()");
  display.u8g2().setFont(u8g2_font_ncenB14_tr);
  auto len = display.u8g2().drawStr(BW(10, 20), "Hello, ");
  display.u8g2().drawStr(RED(10+len, 20), "world!");

  display.u8g2().drawBox(BW(20, 30), 100, 100);

  display.u8g2().drawFrame(RED(60, 80), 150, 170);

  Serial.println("show()");
  display.show();
}

void loop()
{
}
