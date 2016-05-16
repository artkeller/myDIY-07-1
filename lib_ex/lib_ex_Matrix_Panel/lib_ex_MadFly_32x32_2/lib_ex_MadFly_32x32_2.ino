#include <SPI.h>                                  // cf http://arduino.cc/en/Reference/SPI
#define  MOSI         11                          // MOSI (Master-Out-Slave-In) pin
#define  SCK          13                          // SCK (Clock) pin
#define  SS           10                          // SS (Slave Select) pin

#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

// Orientation of Max72xx to 8x8 LED Matrix
#define NO_ROTATION   0                           // no rotation
#define CW_ROTATION   1                           // 90 degrees clockwise
#define OPP_ROTATION  2                           // 180 degrees
#define CCW_ROTATION  3                           // 90 degrees counter clockwise

// Mapping of 8x8 LED Matrix and SPI pin names
#define CS            SS                          // Attach CS to SS
#define DIN           MOSI                        // Attach DIN to MOSI
#define CLK           SCK                         // Attach CLK to SCK

// Configuration of LED Matrix 32x32 (4x4 Displays) - Max72xx Common Cathodes Modules
#define NUMBEROFHORIZONTALDISPLAYS  4
#define NUMBEROFVERTICALDISPLAYS    4
#define ROTATION                    CCW_ROTATION  // display is position 90 degrees counter clockwise
#define DEFAULTINTENSITY            2            // values fro 0 to 15

Max72xxPanel matrix = Max72xxPanel(CS, NUMBEROFHORIZONTALDISPLAYS, NUMBEROFVERTICALDISPLAYS);

void setup() {
  matrix.setIntensity(DEFAULTINTENSITY);

  /**
     Initialize 32x32 LED matrix with 4x4 display array

           0(0,0,0)            1(1,1,0)          2(2,2,0)          3(3,3,0)
           4(4,0,1)            5(5,1,1)          6(6,2,1)          7(7,3,1)
           8(8,0,2)            9(9,1,2)         10(10,2,2)        11(11,3,2)
          12(12,0,3)          13(13,1,3)        14(14,2,3)        15(15,3,3)

          x0..7,y0..7         x8..15,y0..7      x16..23,y0..7     x24..31,y0..7
          x0..7,y8..15        x8..15,y8..15     x16..23,y8..15    x24..31,y8..15
          x0..7,y16..23       x8..15,y16..23    x16..23,y16..23   x24..31,y16..23
          x0..7,y24..31       x8..15,y24..31    x16..23,y24..31   x24..31,y24..31
  */

  byte display = 0;
  for (byte y = 0; y < NUMBEROFVERTICALDISPLAYS; y++ ) {
    for (byte x = 0; x < NUMBEROFHORIZONTALDISPLAYS; x++ ) {
      matrix.setPosition(display, x, y);      // display is at <x, y>
      matrix.setRotation(display, ROTATION);  // display is position -90 degree
      display++;
    }
  }

  // Individual setup
  _setup();
}

int pinRandom = A0;
int wait = 20; // In milliseconds

int x = matrix.width() / 2;   // Read matrix width (x) 
int y = matrix.height() / 2;  // Read matrix height (y) 
int xNext, yNext;

void _setup() {
  randomSeed(analogRead(pinRandom)); // Initialize random generator
}

void loop() {

  matrix.drawPixel(x, y, HIGH);
  matrix.write(); // Send bitmap to display

  delay(wait);

  matrix.drawPixel(x, y, LOW); // Erase the old position of our dot

  do {
    switch ( random(4) ) {
      case 0: xNext = constrain(x + 1, 0, matrix.width() - 1);  yNext = y; break;
      case 1: xNext = constrain(x - 1, 0, matrix.width() - 1);  yNext = y; break;
      case 2: yNext = constrain(y + 1, 0, matrix.height() - 1); xNext = x; break;
      case 3: yNext = constrain(y - 1, 0, matrix.height() - 1); xNext = x; break;
    }
  }
  while ( x == xNext && y == yNext ); // Repeat until we find a new coordinate

  x = xNext;
  y = yNext;
}
