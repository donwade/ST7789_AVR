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

void ST7789_AVR *lcd = new ST7789_AVR(TFT_DC, TFT_RST, TFT_CS, TFT_MOSI, TFT_MISO,
TFT_CLK); void setup()
{
  Serial.begin(9600);
  lcd->init(SCR_WD, SCR_HT);
  font.init(customRect, SCR_WD, SCR_HT); // custom fillRect function and screen width and height values

  for(int i=0;i<256;i+=16) {
    uint8_t r,g,b;
    lcd->rgbWheel(i*512L/256,&r,&g,&b);
    lcd->fillRect(0,i,240,16,RGBto565(r,g,b));
  }

  font.setFont(&rre_chicago_20x24); font.setSpacing(2);
  font.setScale(2);
  font.setColor(BLACK);
  font.printStr(ALIGN_CENTER,60+2,"SCROLL"); font.printStr(ALIGN_CENTER,140+2,"DEMO");
  font.setColor(WHITE);
  font.printStr(ALIGN_CENTER,60,"SCROLL"); font.printStr(ALIGN_CENTER,140,"DEMO");
  font.setScale(1);
  delay(2000);
}

int bgCols[] = {6,8,10,12,14,12,10,8};
char *scrollTxt[] = {"","This","is","an example","of","super-smooth","scrolling","with regular",
                     "AVR Arduino,","ST7789","240x240 IPS LCD","library","and","RRE Fonts",""};

int c=0,t=0;
int maxy=320; // internal ST7789 fb is 240x320
unsigned long ms;

void loop()
{
  // full screen scrolling
  lcd->setScrollArea(0,0);
  font.setSpacing(2);
  for(int l=0;l<3;l++)
  for(int i=0;i<maxy;i++) {
    ms = millis();
    lcd->setScroll(i);
    int y=i+256;
    if(y>=maxy) y-=maxy;
    if((i%32)==0) {
      lcd->fillRect(0,y,240,32,RGBto565(0,0,bgCols[c]<<4));
      font.printStr(ALIGN_CENTER,y+5,scrollTxt[t]);
      if(++c>=sizeof(bgCols)/sizeof(bgCols[0])) c=0;
      if(++t>=sizeof(scrollTxt)/sizeof(scrollTxt[0])) t=0;
      //Serial.println(millis()-ms); // less than 25ms per line
    }
    while(millis()-ms<25);
  }

  // scrolling with fixed top area
  lcd->fillRect(0,0,240,6,RGBto565(220,0,220));
  lcd->fillRect(0,6,240,64-12,RGBto565(180,0,180));
  lcd->fillRect(0,64-6,240,6,RGBto565(140,0,140));
  font.setScale(1,2); font.setSpacing(3);
  font.setColor(YELLOW);
  font.printStr(ALIGN_CENTER,4*2,"Fixed Top Area");
  font.setColor(WHITE);
  font.setScale(1); font.setSpacing(3);
  lcd->setScrollArea(64, 0);
  for(int l=0;l<3;l++)
  for(int i=64;i<maxy;i++) {
    ms = millis();
    lcd->setScroll(i);
    int y=i+256-64;
    if(y>=maxy) {y-=maxy; y+=64;}
    if((i%32)==0) {
      lcd->fillRect(0,y,240,32,RGBto565(0,0,bgCols[c]<<4));
      font.printStr(ALIGN_CENTER,y+5,scrollTxt[t]);
      if(++c>=sizeof(bgCols)/sizeof(bgCols[0])) c=0;
      if(++t>=sizeof(scrollTxt)/sizeof(scrollTxt[0])) t=0;
    }
    while(millis()-ms<25);
  }
}

