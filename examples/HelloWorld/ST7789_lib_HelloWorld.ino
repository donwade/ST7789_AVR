// ST7789 library example
// (c) 2019 Pawel A. Hernik

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

