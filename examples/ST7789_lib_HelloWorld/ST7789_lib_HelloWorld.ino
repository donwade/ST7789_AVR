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

#define TFT_MOSI   23  //GREEN data out
#define TFT_CLK    18  // ORANGE
#define TFT_DC     19   // BLUE     pass blinky
#define TFT_CS     13   // YELLOW   pass blinky
#define TFT_RST    5    // BROWN    pass blinky


#define BLINKY_TEST
#ifdef BLINKY_TEST
#define BLINK_BLUE_LED 2
#define BLINK_ONE_LED TFT_DC    //BLUE
#define BLINK_TWO_LED TFT_CS    //YELLOW
#define BLINK_RST_LED TFT_RST   //BROWN
#define BLINK_CLK_LED TFT_CLK   // ORANGE normally spi provided
#define BLINK_OUT_LED TFT_MOSI

void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(BLINK_BLUE_LED, OUTPUT);
    pinMode(BLINK_ONE_LED, OUTPUT);
    pinMode(BLINK_TWO_LED, OUTPUT);
    pinMode(BLINK_RST_LED, OUTPUT);
    pinMode(BLINK_CLK_LED, OUTPUT);
    pinMode(BLINK_OUT_LED, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(BLINK_BLUE_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(BLINK_ONE_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(BLINK_TWO_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(BLINK_RST_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(BLINK_CLK_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(BLINK_OUT_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(BLINK_BLUE_LED, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(BLINK_ONE_LED, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(BLINK_TWO_LED, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(BLINK_RST_LED, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(BLINK_CLK_LED, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(BLINK_OUT_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

#else

#define SCR_WD 240
#define SCR_HT 240

ST7789_AVR lcd = ST7789_AVR(TFT_DC, TFT_RST, TFT_CS);

void setup(void)
{
  Serial.begin(115200);
  lcd.init(SCR_WD, SCR_HT);
  lcd.fillScreen(RED);
  lcd.setCursor(0, 0);
  lcd.setTextColor(WHITE,BLUE);
  lcd.setTextSize(3);
  lcd.println("HELLO WORLD"); // using Adafruit default font
 }

void loop()
{
    delay(-1);
}

#endif

