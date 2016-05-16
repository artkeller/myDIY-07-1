//
//      FILE: lib_ex_Plasma_B_32x32_2/lib_ex_Plasma_B_32x32_2.ino
//    AUTHOR: Thomas Walloschke
//   VERSION: 0.3.2
//   PURPOSE: 32x32 LED Matrix Application (16x8x8 MC) - "Arduino Sketch" - Plasma
//      DATE: 2016-03-10
//   CONTACT: artkeller(at)gmx.de
// COPYRIGHT: © 2016 Thomas Walloschke
//   LICENSE: The MIT License (MIT)
//            Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
//            associated documentation files (the “Software”), to deal in the Software without restriction, including
//            without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//            copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
//            following conditions:
//
//            The above copyright notice and this permission notice shall be included in all copies or substantial
//            portions of the Software.
//
//            THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
//            LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//            IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//            SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//////////////////////////////////////////////////////////////////////////////////////////
//
// Matrix Panel Setup Frame
// ************************

#include "config.h"       // local - masters all the matrix panel magic

void setup() {
  setupMatrix();          // cf. config.h - 32x32 LED Matrix Panel Basic Setup
  setupApp();             // cf. below    - indiv. setup
}

void loop() {
  loopApp();
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Matrix Panel Functional Frame
// *****************************

byte matrixWidth  = matrix.width();   // Read matrix width (x)
byte matrixHeight = matrix.height();  // Read matrix height (y)

// Convenient 2D point structure
struct Point {
  float x;
  float y;
};

float phase = float(random(360e10));  // TODO: Overvlow Handling!
float phaseIncrement = 0.04;          // Controls the speed of the moving points. Higher == faster. I like 0.08 .
float colorStretch = 0.07;            // Higher numbers will produce tighter color bands. I like 0.11 .

//
void setupApp() {}

//
void loopApp() {

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
      float color_f = ( log( distance * colorStretch ) + 1.0 ) * 0.5;  // range: 0.0...1.0

      // Square the color_f value to weight it towards 0. The image will be darker and have higher contrast.
      color_f *= color_f;
      color_f *= color_f * color_f * color_f;  // Uncomment this line to make it even darker :)
      color_f *= color_f * color_f ;

      // Scale the color up to 0..7 . Max brightness is 7.
      DRAW_PIXEL(row, col, byte( round(color_f * 7.0)));
    }
  }

  WRITE_SCREEN(); // Send bitmap to display
}

