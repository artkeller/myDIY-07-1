//
//      FILE: lib_ex_Plasma_B_32x32_2/config.h
//    AUTHOR: Thomas Walloschke
//   VERSION: 0.3.2
//   PURPOSE: 32x32 LED Matrix Application (16x8x8 MC) - Configuration File - ...
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

#ifndef  CONFIG_H
#define  CONFIG_H

#include "Arduino.h"

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Application Configuration

#define  DEBUG        true                          // alpha version
// ...

///////////////////////////////////////////// NO CONFIGURABLE PARTS BELOW THIS POINT
//
//  DEBUG Settings

#if     DEBUG
// ...
#endif  // DEBUG

/////////////////////////////////////////////
//
//  Functional Settings

// ...

//////////////////////////////////////////////////////////////////////////////////////////
//
//  32x32 LED Matrix Basic Settings

// -- Load LED Matrix Libraries
#include <SPI.h>                                    // cf. http://arduino.cc/en/Reference/SPI
#include <Adafruit_GFX.h>                           // cf. https://github.com/adafruit/Adafruit-GFX-Library
#include <Max72xxPanel.h>                           // cf. https://github.com/markruys/arduino-Max72xxPanel

// -- SPI Supported MCU Boards
//    cf. http://arduino.cc/en/Reference/SPI
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_LILYPAD) \
 || ( (TEENSYDUINO == 127) and ( defined(__MKL26Z64__) or defined(__MK20DX128__) or defined(__MK20DX256__) or 1 ) )
#define  MOSI         11                            // MOSI (Master-Out-Slave-In) pin - <documentation>, cf. SPI, adopted to MCU 
#define  SCK          13                            // SCK (Serial Clock) pin         - <documentation>, cf. SPI, adopted to MCU 
#define  SS           10                            // SS (Slave Select) pin          - configured
#else    // Unsupported MCU Boards
#error   "MCU BOARD has NOT been defined in the <config.h> file as SPI master and was NOT tested"
#endif   // end MCU Boards

// -- Orientation of Max72xx and 8x8 LED Matrix Module
//    cf. https://github.com/markruys/arduino-Max72xxPanel
//    Based on Adafruit's GFX rotation
#define NO_ROTATION   0                             // no rotation
#define CW_ROTATION   1                             // 90 degrees clockwise
#define VAV_ROTATION  2                             // 180 degrees - vis-a-vis
#define CCW_ROTATION  3                             // 90 degrees counter clockwise

// -- Mapping of 8x8 LED Matrix to SPI pin names
//    http://playground.arduino.cc/Main/LEDMatrix
//    Based on Max72xx and SPI nomenclature
#define CS            SS                            // Attach CS  to SS               - <documentation>, cf. Max72xx LED Matrix Module
#define DIN           MOSI                          // Attach DIN to MOSI             - <documentation>, cf. Max72xx LED Matrix Module
#define CLK           SCK                           // Attach CLK to SCK              - <documentation>, cf. Max72xx LED Matrix Module

// -- Configuration of 32x32 LED Matrix Panel (4x4 x 8x8 LED Matrix Modules)
//    Max72xx Common Cathodes(!)
//    cf. http://pdfserv.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
//    cf. http://www.aliexpress.com/item/MAX7219-dot-matrix-module-microcontroller-module-16-in-one-display/32338538461.html
#define NUMBER_OF_HORIZONTAL_MODULES  4
#define NUMBER_OF_VERTICAL_MODULS     4
#define ROTATION                      CCW_ROTATION  // modules' positions are 90 degrees counter clockwise

// -- Convenience Interface
#define MATRIX_PANEL()                Max72xxPanel(CS, NUMBER_OF_HORIZONTAL_MODULES, NUMBER_OF_VERTICAL_MODULS)

// -- Panel intensity
#define MIN_INTENSITY                 0
#define NORMAL_INTENSITY              7
#define MAX_INTENSITY                 15
#define DEFAULT_INTENSITY             MIN_INTENSITY // values from 0 to 15 - default=0 (Max72xxPanel sets default=7)

// -- Draw mapping Macros
#define DRAW_PIXEL(row, col, color)                 matrix.drawPixel(row, col, color)
#define DRAW_LINE(row1, col1, row2, col2)           matrix.drawLine(row1, col1, row2, col2, HIGH)
#define DRAW_CHAR(row, col, character)              matrix.drawChar(row, col, character, HIGH, LOW, 1)

// -- Modul mapping Macros
#define SET_MODUL_POSITION(module, x, y)            matrix.setPosition(module, x, y)
#define SET_MODUL_ROTATION(module, rotation)        matrix.setRotation(module, rotation & 0x03)

// -- Screen mapping Macros
#define SET_SCREEN_INTENSITY(intensity)             matrix.setIntensity(intensity & 0x0f)
#define SET_SCREEN_ROTATION(rotation)               matrix.setRotation(rotation & 0x03)
#define TEST_SCREEN()                               matrix.fillScreen(HIGH); matrix.write()
#define RESET_SCREEN()                              matrix.fillScreen(LOW); matrix.write()
#define CLEAR_SCREEN()                              matrix.fillScreen(LOW)
#define WRITE_SCREEN()                              matrix.write()

// -- Constructor
Max72xxPanel matrix = MATRIX_PANEL();

void  setupMatrix() {

  SET_SCREEN_INTENSITY(DEFAULT_INTENSITY);

  /**
     Initialize 32x32 LED matrix as 8x4x4 display array

     Module/Position
           0(0,0,0)            1(1,1,0)          2(2,2,0)          3(3,3,0)
           4(4,0,1)            5(5,1,1)          6(6,2,1)          7(7,3,1)
           8(8,0,2)            9(9,1,2)         10(10,2,2)        11(11,3,2)
          12(12,0,3)          13(13,1,3)        14(14,2,3)        15(15,3,3)

      X/Y-Coordinates
          x0..7,y0..7         x8..15,y0..7      x16..23,y0..7     x24..31,y0..7
          x0..7,y8..15        x8..15,y8..15     x16..23,y8..15    x24..31,y8..15
          x0..7,y16..23       x8..15,y16..23    x16..23,y16..23   x24..31,y16..23
          x0..7,y24..31       x8..15,y24..31    x16..23,y24..31   x24..31,y24..31
  */

  byte module = 0;
  for (byte y = 0; y < NUMBER_OF_VERTICAL_MODULS; y++ ) {
    for (byte x = 0; x < NUMBER_OF_HORIZONTAL_MODULES; x++ ) {
      SET_MODUL_POSITION(module, x, y);      // module is at <x, y>
      SET_MODUL_ROTATION(module, ROTATION);  // module rotation to setup a standard matrix panel (0,0 is left side up)
      module++;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

#endif // end CONFIG_H

//////////////////////////////////////////////////////////////////////////////////////////

/* end-of-header-file */
