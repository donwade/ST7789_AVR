// ST7789 library example
// (c) 2019-24 Pawel A. Hernik


#include <SPI.h>
#include <Adafruit_GFX.h>
#include "ST7789_AVR.h"

#define SCR_WD ST7789_TFTWIDTH
#define SCR_HT ST7789_TFTHEIGHT
ST7789_AVR *lcd = new ST7789_AVR(ENGINE_HSPI, TFT_DC, TFT_RST, TFT_CS, TFT_MOSI, TFT_MISO, TFT_CLK);
void setup()
{
  Serial.begin(115200);
  lcd->init(SCR_WD,SCR_HT);
  lcd->setRotation(0);
}

void loop(void)
{
  for(uint8_t rot = 0; rot < 4; rot++) {
    testText(rot);
    delay(2000);
  }
}

unsigned long testText(int rot)
{
  lcd->setRotation(rot);
  lcd->fillScreen(BLACK);
  lcd->setCursor(0, 0);
  lcd->setTextColor(BLUE);
  lcd->setTextSize(1);
  lcd->println("Hello World!");
  lcd->setTextColor(WHITE);
  lcd->print("Rotation = ");
  lcd->println(rot);
  lcd->setTextColor(YELLOW);
  lcd->setTextSize(2);
  lcd->println(1234.56);
  lcd->setTextColor(RED);
  lcd->setTextSize(3);
  lcd->println(0xDEAD, HEX);
  lcd->println();
  lcd->setTextColor(GREEN);
  lcd->setTextSize(4);
  lcd->println("Hello");
}


