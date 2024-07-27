// ST7789 library example
// (c) 2019 Pawel A. Hernik

/*
ST7789 240x240 1.3" IPS (without CS pin) - only 4+2 wires required:
 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/SCK
 #04 SDA -> D11/MOSI
 #05 RES -> D9 /PA0 or any digital (HW RESET is required to properly initialize LCD without CS)
 #06 DC  -> D10/PA1 or any digital
 #07 BLK -> NC

ST7789 240x280 1.69" IPS - only 4+2 wires required:
 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/SCK
 #04 SDA -> D11/MOSI
 #05 RES -> optional
 #06 DC  -> D10 or any digital
 #07 CS  -> D9 or any digital
 #08 BLK -> VCC

ST7789 170x320 1.9" IPS - only 4+2 wires required:
 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/SCK
 #04 SDA -> D11/MOSI
 #05 RES -> optional
 #06 DC  -> D10 or any digital
 #07 CS  -> D9 or any digital
 #08 BLK -> VCC

ST7789 240x320 2.0" IPS - only 4+2 wires required:
 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/SCK
 #04 SDA -> D11/MOSI
 #05 RES -> optional
 #06 DC  -> D10 or any digital
 #07 CS  -> D9 or any digital
*/

#include <SPI.h>
#include "ST7789_AVR.h"
#include <Adafruit_GFX.h>

#define SCR_WD ST7789_TFTWIDTH
#define SCR_HT ST7789_TFTHEIGHT

void setup(void)
{
  Serial.begin(115200);

  lcd.init(SCR_WD, SCR_HT);
  lcd.clearScreen();

  lcd.fillScreen(RED);
  lcd.enableDisplay(true);
  printf("%s %d\n", __FUNCTION__, __LINE__);
  delay(5000);

  lcd.setCursor(0, 0);
  printf("%s %d\n", __FUNCTION__, __LINE__);
  lcd.setTextColor(WHITE,BLUE);
  printf("%s %d\n", __FUNCTION__, __LINE__);
  lcd.setTextSize(3);
  printf("%s %d\n", __FUNCTION__, __LINE__);

  lcd.powerSave(2);
  lcd.enableDisplay(true);
 }

void loop()
{
    static unsigned long cnt;
    lcd.println(cnt++); // using Adafruit default font
}

