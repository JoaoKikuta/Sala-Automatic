#include <EEPROM.h>

#include <SPI.h>

#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <Adafruit_ST7735.h>


#include "bitmaps.h"
#include "bitmapsLarge.h"


#define TFT_CS     10
#define TFT_RST    8 
#define TFT_DC     9

//char img = "bitmaps.h";
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void setup() {
 // EEPROM.write(0, img);
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(1);
	tft.fillScreen(ST7735_BLACK);





  int h = 128,w = 97, row, col, buffidx=0;
  for (row=0; row<h; row++) { // For each scanline...
    for (col=0; col<w; col++) { // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col, row, pgm_read_word(evive_in_hand + buffidx));
      buffidx++;
    } // end pixel
  }
}

void loop() {
  
}
