// ST7789 library example
// (c) 2019-24 Pawel A. Hernik

// requires RRE Font library:
// https://github.com/cbm80amiga/RREFont


#include <SPI.h>
#include <Adafruit_GFX.h>
#include "ST7789_AVR.h"

#define SCR_WD ST7789_TFTWIDTH
#define SCR_HT ST7789_TFTHEIGHT

#include "RREFont.h"
#include "rre_chicago_20x24.h"

RREFont font;

// needed for RREFont library initialization, define your fillRect
void customRect(int x, int y, int w, int h, int c) { return lcd->fillRect(x, y, w, h, c); }

ST7789_AVR *lcd = new ST7789_AVR(ENGINE_HSPI);

void setup()
{
  Serial.begin(115200);
  lcd->init(SCR_WD, SCR_HT);
  font.init(customRect, SCR_WD, SCR_HT); // custom fillRect function and screen width and height values
  font.setFont(&rre_chicago_20x24);
  font.setScale(1,2); font.setSpacing(3);
  font.setColor(WHITE);
}

void rainbow()
{
  for(int i=0;i<240;i+=4) {
    uint8_t r,g,b;
    lcd->rgbWheel(i*512L/240,&r,&g,&b);
    lcd->fillRect(0,i,240,4,RGBto565(r,g,b));
  }
}

void loop()
{
  lcd->fillScreen(RGBto565(120,60,30));
  font.printStr(ALIGN_CENTER,95,"ST7789 modes");
  delay(2000);

  lcd->powerSave(7);
/*
  rainbow(); delay(2000);
  lcd.setBrightness(0);    delay(2000);
  lcd.setBrightness(128);  delay(2000);
  lcd.setBrightness(255);  delay(2000);
*/
  rainbow();
  font.setColor(BLACK);
  font.printStr(ALIGN_CENTER,95,"Idle mode OFF");
  lcd->idleDisplay(false); delay(2000);
  rainbow();
  font.printStr(ALIGN_CENTER,95,"Idle mode ON");
  lcd->idleDisplay(true); delay(4000);
  rainbow();
  font.printStr(ALIGN_CENTER,95,"Idle mode OFF");
  lcd->idleDisplay(false); delay(2000);

  rainbow();
  font.setColor(WHITE,BLACK);
  lcd->fillRect(30,87,240-60,60,BLACK);
  font.printStr(ALIGN_CENTER,95,"Invert OFF");
  lcd->invertDisplay(false); delay(2000);
  font.printStr(ALIGN_CENTER,95," Invert ON ");
  lcd->invertDisplay(true); delay(4000);
  font.printStr(ALIGN_CENTER,95,"Invert OFF");
  lcd->invertDisplay(false); delay(2000);

  font.setColor(WHITE);
  lcd->fillScreen(RGBto565(180,0,180));
  font.printStr(ALIGN_CENTER,95,"Sleep mode in 2s");
  delay(2000);
  //lcd.enableDisplay(false);
  lcd->sleepDisplay(true); delay(4000);
  lcd->sleepDisplay(false);
  //lcd.enableDisplay(true);

  lcd->fillScreen(RGBto565(180,0,180));
  font.printStr(ALIGN_CENTER,95,"Display on/off");
  delay(2000);
  lcd->enableDisplay(false);  delay(4000);
  lcd->enableDisplay(true);  delay(1000);

  lcd->fillScreen(RGBto565(180,0,180));
  font.printStr(ALIGN_CENTER,95,"Partial display");
  font.setColor(YELLOW);
  font.printStr(ALIGN_CENTER,6,"Top");
  font.printStr(ALIGN_CENTER,240-50,"Bottom");
  font.setColor(WHITE);
  delay(2000);
  lcd->setPartArea(60*1, 60*3); lcd->partialDisplay(true); delay(4000);
  lcd->setPartArea(60*3, 60*1); lcd->partialDisplay(true); delay(4000);
  lcd->partialDisplay(false);
  delay(1000);

  lcd->fillScreen(RGBto565(180,0,0));
  font.printStr(ALIGN_CENTER,95,"Sw reset ...");
  delay(2000);
  lcd->resetDisplay();  delay(2000);
  lcd->init(SCR_WD, SCR_HT);
  lcd->fillScreen(RGBto565(0,0,180));
  font.printStr(0,0,"After reset"); delay(2000);
}

