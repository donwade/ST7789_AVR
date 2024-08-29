// Fast ST7789 IPS 240x240 SPI display library
// (c) 2019-24 by Pawel A. Hernik

#ifndef _ST7789_AVR_H_
#define _ST7789_AVR_H_

// ------------------------------
// define for LCD boards where CS pin is internally connected to the ground
//#define CS_ALWAYS_LOW
// ------------------------------

#include "Arduino.h"
//#include "Print.h"
#include <Adafruit_GFX.h>
//#include <avr/pgmspace.h>

#define ST7789_TFTWIDTH 	240
#define ST7789_TFTHEIGHT 	280 //dwade

#define ST7789_RAMWIDTH 	240
#define ST7789_RAMHEIGHT 	320 //dwade


// Color definitions

#define RGBto565(r,g,b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))
#define RGBIto565(r,g,b,i) ((((((r)*(i))/255) & 0xF8) << 8) | ((((g)*(i)/255) & 0xFC) << 3) | ((((b)*(i)/255) & 0xFC) >> 3))

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define	GREY  RGBto565(128,128,128)
#define	LGREY RGBto565(160,160,160)
#define	DGREY RGBto565( 80, 80, 80)

#define	LBLUE RGBto565(100,100,255)
#define	DBLUE RGBto565(  0,  0,128)

typedef enum SPI_ENGINE
{
    ENGINE_NONE,
    ENGINE_HSPI,
    ENGINE_VSPI
};

class ST7789_AVR : public Adafruit_GFX {

 public:
  //ST7789_AVR(SPI_ENGINE ok, int8_t DC, int8_t RST=-1, int8_t CS=-1, int8_t MOSI=-1, int8_t MISO=-1, int8_t  CLK=-1);
  ST7789_AVR(SPI_ENGINE who);

  void init(uint16_t wd, uint16_t ht);
  void begin() { init(ST7789_TFTWIDTH,ST7789_TFTHEIGHT); }
  void speed(uint32_t speed);
  void init() { init(ST7789_RAMWIDTH,ST7789_RAMHEIGHT); }
  void setAddrWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);
  void pushColor(uint16_t color);
  void fillScreen(uint16_t color=BLACK);
  void clearScreen() { fillScreen(BLACK); }
  void cls() { fillScreen(BLACK); }
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  void drawImage(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *img);
  void drawImageF(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *img16);
  void drawImageF(int16_t x, int16_t y, const uint16_t *img16) { drawImageF(x,y,pgm_read_word(img16),pgm_read_word(img16+1),img16+3); }
  void setRotation(uint8_t r);
  void invertDisplay(boolean mode);
  void partialDisplay(boolean mode);
  void sleepDisplay(boolean mode);
  void enableDisplay(boolean mode);
  void idleDisplay(boolean mode);
  void resetDisplay();
  void setScrollArea(uint16_t tfa, uint16_t bfa);
  void setScroll(uint16_t vsp);
  void setPartArea(uint16_t sr, uint16_t er);
  void setBrightness(uint8_t br);
  void powerSave(uint8_t mode);

  void viewPort(int16_t window_x, int16_t window_y,
            int16_t window_w, int16_t window_h,
            int16_t source_x, int16_t source_y,
            int16_t source_w, int16_t source_h,
            uint16_t *pRGB565);

  uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);
  uint16_t color565(uint8_t r, uint8_t g, uint8_t b) { return Color565(r, g, b); }
  void rgbWheel(int idx, uint8_t *_r, uint8_t *_g, uint8_t *_b);
  uint16_t rgbWheel(int idx);

 protected:
  uint16_t xstart, ystart, xend, yend, xoffs, yoffs; // values can be > 256!!!
  uint16_t _widthIni, _heightIni;

  void displayInit(const uint8_t *addr);
  void writeSPI(uint8_t);
  void writeMulti(uint16_t color, uint32_t num);
  void copyMulti(uint8_t *img, uint32_t num);
  void writeCmd(uint8_t c);
  void writeData(uint8_t d8);
  void writeData16(uint16_t d16);
  void commonST7789Init(const uint8_t *cmdList);

 private:
  int8_t  csPin, dcPin, rstPin, mosiPin, misoPin, clkPin ;
  uint8_t  csMask, dcMask;
  SPI_ENGINE select;

  //uninitialised pointers to SPI objects
  SPIClass *aSPI = NULL;

  volatile uint8_t  *csPort, *dcPort;
};

void dprintf( const char *format, ...);

// setup global LCD
extern ST7789_AVR *lcd;

typedef struct PINOUT
{
    int8_t mosi_pin;   // GREEN   vspi classic
    int8_t miso_pin;   // not used vspi classic
    int8_t clk_pin;    // ORANGE vspi classic
    int8_t dc_pin;     // BLUE   user defined
    int8_t cs_pin;     // YELLOW vspi classic
    int8_t rst_pin;    // BROWN  user defined
    int8_t blgt_pin;   // GREY   user defined  DAC1 brightness
};


#define TFT_3v3 // purple
#define TFT_GND // white

const PINOUT WROVER_VSPI
{
    .mosi_pin = 23,  // GREEN   vspi classic
    .miso_pin = 19,  // not used vspi classic
    .clk_pin  = 18,  // ORANGE vspi classic
    .dc_pin   =  4,  // BLUE   user defined
    .cs_pin   =  5,  // YELLOW vspi classic
    .rst_pin  = 13,  // BROWN  user defined
    .blgt_pin = 25,  // GREY   user defined  DAC1 brightness
};

const PINOUT WROVER_HSPI
{
    .mosi_pin = 13,  // GREEN    hspi classic
    .miso_pin = -1,  // not used hspi classic
    .clk_pin  = 14,  // ORANGE  hspi classic
    .dc_pin   = 32,  // BLUE    user defined
    .cs_pin   = 33,  // YELLOW  hspi classic
    .rst_pin  = -1,  // BROWN   cant find a pin
    .blgt_pin = -1,  // GREY    user defined  DAC1 brightness
};

const PINOUT WROOM_HSPI
{
    .mosi_pin = 40,  //GREEN    hspi classic
    .miso_pin = -1,  // not used hspi classic
    .clk_pin  = 39,  // ORANGE  hspi classic
    .dc_pin   = 38,  // BLUE    user defined
    .cs_pin   = 47,  // YELLOW  hspi classic
    .rst_pin  = 21,  // BROWN   cant find a pin
    .blgt_pin = -1   // GREY    user defined  DAC1 brightness
};

#define Stringize( L )     #L
#define MakeString( M, L ) M(L)
#define $Line MakeString( Stringize, __LINE__ )
#define Reminder __FILE__ "(" $Line ") : Reminder: "
#pragma message(Reminder "Fix this problem!")

#define XSTR(x) STR(x)
#define STR(x) #x
/*
#pragma message ("TFT_MOSI  = " XSTR(TFT_MOSI))
#pragma message ("TFT_MISO  = " XSTR(TFT_MISO))
#pragma message ("TFT_CLK   = " XSTR(TFT_CLK))
#pragma message ("TFT_DC    = " XSTR(TFT_DC))
#pragma message ("TFT_CS    = " XSTR(TFT_CS))
#pragma message ("TFT_RST   = " XSTR(TFT_RST))
#pragma message ("TFT_BLGT  = " XSTR(TFT_BLGT))
*/

#endif
