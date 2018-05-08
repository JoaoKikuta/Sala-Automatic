#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

// pin definition for the Leonardo
// #define cs   7
// #define dc   0
// #define rst  1

TFT TFTscreen = TFT(cs, dc, rst);

// position of the line on screen
int xPos = 0;

void setup() {
  // initialize the serial port
  Serial.begin(9600);

  // initialize the display
  TFTscreen.begin();

  // clear the screen with a pretty color
  TFTscreen.background(0, 0, 0);
}

void loop() {
  // read the sensor and map it to the screen height
  int sensor = analogRead(A0);
  int drawHeight = map(sensor, 0, 1023, 0, TFTscreen.height());

  // print out the height to the serial monitor
  Serial.println(drawHeight);

  // draw a line in a nice color
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.line(xPos, TFTscreen.height() - drawHeight, xPos, TFTscreen.height());

  // if the graph has reached the screen edge
  // erase the screen and start again
  if (xPos >= 160) {
    xPos = 0;
    TFTscreen.background(0, 0, 0);
  } else {
    // increment the horizontal position:
    xPos++;
  }

  delay(16);
}
