#include <SPI.h>                                  // cf http://arduino.cc/en/Reference/SPI
#define  MOSI         11                          // MOSI (Master-Out-Slave-In) pin
#define  SCK          13                          // SCK (Serial Clock) pin
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

//////////////////////////////////////////////////////////////////////////////////////////
//
// Standard Setup of LED Matrix 32x32 (4x4 Displays) - Max72xx Common Cathodes Modules
// =================================================
//

#define NUMBEROFHORIZONTALDISPLAYS  4
#define NUMBEROFVERTICALDISPLAYS    4
#define ROTATION                    CCW_ROTATION  // display is position 90 degrees counter clockwise
#define DEFAULTINTENSITY            1             // values fro 0 to 15

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

//////////////////////////////////////////////////////////////////////////////////////////
//
// Individual Functions
// ====================

// Functional mapping to 8x8 LED matrix
#define CLEAR_SCREEN()                matrix.fillScreen(LOW)
#define DRAW_PIXEL(row, col, color)   matrix.drawPixel(row, col, color)
#define WRITE_SCREEN()                matrix.write()

byte matrixWidth  = matrix.width();   // Read matrix width (x)
byte matrixHeight = matrix.height();  // Read matrix height (y)

// Convenient 2D point structure
struct Point {
  float x;
  float y;
};

float phase = 0.0;
float phaseIncrement = 0.04;          // Controls the speed of the moving points. Higher == faster. I like 0.08 .
float colorStretch = 0.07;            // Higher numbers will produce tighter color bands. I like 0.11 .

//
void _setup() {}

//
void loop() {

  phase += phaseIncrement;

  /**
     The two points move along Lissajous curves, see: http://en.wikipedia.org/wiki/Lissajous_curve
     We want values that fit the LED grid: x values between 0..13, y values between 0..8 .
     The sin() function returns values in the range of -1.0..1.0, so scale these to our desired ranges.
     The phase value is multiplied by various constants; I chose these semi-randomly, to produce a nice motion.
  */
  Point p1 = { (sin(phase * 1.000) + 1.0) * 7.5, (sin(phase * 1.310) + 1.0) * 4.0 };
  Point p2 = { (sin(phase * 1.770) + 1.0) * 7.5, (sin(phase * 2.865) + 1.0) * 4.0 };

  CLEAR_SCREEN();

  byte row, col;

  // For each row...
  for ( row = 0; row < matrixWidth; row++ ) {
    float row_f = float(row);  // Optimization: Keep a floating point value of the row number, instead of recasting it repeatedly.

    // For each column...
    for ( col = 0; col < matrixHeight; col++ ) {
      float col_f = float(col);  // Optimization.

      // Calculate the distance between this LED, and p1.
      Point dist1 = { col_f - p1.x, row_f - p1.y };  // The vector from p1 to this LED.
      float distance = dist1.x * dist1.x + dist1.y * dist1.y;

      // Calculate the distance between this LED, and p2.
      Point dist2 = { col_f - p2.x, row_f - p2.y };  // The vector from p2 to this LED.
      // Multiply this with the other distance, this will create weird plasma values :)
      distance *= dist2.x * dist2.x + dist2.y * dist2.y;
      distance = sqrt(distance);

      // Warp the distance with a sin() function. As the distance value increases, the LEDs will get light,dark,light,dark,etc...
      // You can use a cos() for slightly different shading, or experiment with other functions. Go crazy!
      float color_f = ( sin( distance * colorStretch ) + 1.0 ) * 0.5;  // range: 0.0...1.0

      // Square the color_f value to weight it towards 0. The image will be darker and have higher contrast.
      color_f *= color_f;
      //color_f *= color_f * color_f * color_f;  // Uncomment this line to make it even darker :)

      // Scale the color up to 0..7 . Max brightness is 7.
      DRAW_PIXEL(row, col, byte( round(color_f * 7.0)));
    }
  }

  WRITE_SCREEN(); // Send bitmap to display
}

