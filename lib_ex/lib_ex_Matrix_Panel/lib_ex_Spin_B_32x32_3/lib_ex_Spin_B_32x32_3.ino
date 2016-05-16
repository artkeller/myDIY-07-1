//
//      FILE: lib_ex_Spin_B_32x32_3/lib_ex_Spin_B_32x32_3.ino
//    AUTHOR: Thomas Walloschke
//   VERSION: 0.3.2
//   PURPOSE: 32x32 LED Matrix Application (16x8x8 MC) - "Arduino Sketch" - Spinning Clock (see below > Plaything.Time.Scrapes < )
//      DATE: 2016-03-05
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
  _loop();
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Matrix Panel Functional Frame
// *****************************

// -- Character sizing
#define CHARACTER_5x7_WIDTH                         5
#define CHARACTER_5x7_HEIGTH                        7
#define CHARACTER_SPACING                           1

#define CHARACTER_SHAPE_WIDTH                       (CHARACTER_5x7_WIDTH + CHARACTER_SPACING)
#define CHARACTER_SHAPE_HEIGTH                      (CHARACTER_5x7_HEIGTH + CHARACTER_SPACING)

// -- Matrix sizing
byte matrixWidth  = matrix.width();                 // Read matrix width (x)
byte matrixHeight = matrix.height();                // Read matrix height (y)

// Convenient 2D point structure
struct Point {
  byte x;
  byte y;
};

// Start points of submatrices
Point p0  = {byte(0),               byte(0)};
Point p1  = {byte(matrixWidth - 1), byte(0)};
Point p2  = {byte(0),               byte(matrixHeight - 1)};
Point p3  = {byte(matrixWidth - 1), byte(matrixHeight - 1)};

// -- Functional Time mapping
#define SYNC_DATE_TIME()                            breakTime(syncMagicTime(), tm)

// -- DateTime references
//    cf. "date_timeProvider.ino"-tab
#include <Time.h>                                   // cf. http://www.arduino.cc/playground/Code/Time
extern tmElements_t    tm;                          // Time elements

// -- Pattern values
#define START_WAIT_VALUE        40
#define UPPER_WAIT_VALUE        60
#define LOWER_WAIT_VALUE        0
#define START_INCREMENT_VALUE   -2
#define COUNTDOWN_VALUE         -1
#define COUNTUP_VALUE           4

int wait = START_WAIT_VALUE;
int inc  = START_INCREMENT_VALUE;

// -- Indivudual Setup
void setupApp() {
  setupTimeProvider();                              // Set internal clock (time_h) - cf. date_timeProvider.ino
}

////////////////////////////////////////////////////////////////////
//
//  > Plaything.Time.Scrapes <
//  ====================================
//
//    Suddenly I liked to get rid of thinking-by-fixed-pattern:
//    "...a clock is a boring thing and can be seen as a conventional clock only..."
//
//    The basic principle here is the assumption to show time totally fragmented.
//    This elegantly aesthetic machine offers subliminal attention to the observer
//    due to the fact, that the trained typical regular time presentation decamped
//    and that requirement of an interpretation of the fragments.
//    The observer may be aware to rethink time and develop such as understanding, 
//    respect and empathy for scrapes of time in his own life. The power of our 
//    love of order is boring and unrewarding. One can fall in love with time scrapes.
//    
//
//    Conclusion: Time is thus rendered a plaything with sometimes no meaning at all.
//

void _loop() {

  // -- Show HOUR ten's digit and SECOND single digit
  for ( int x = 0; x < matrixWidth - 1; x++ ) {
    CLEAR_SCREEN();
    DRAW_LINE(x, 0, matrixWidth - 1 - x, matrixHeight - 1);
    SYNC_DATE_TIME();
    DRAW_CHAR(x, 0 + CHARACTER_SPACING, '0' + ( bin2bcd(tm.Hour) >> 4 ) );
    DRAW_CHAR( p3.x - x / 2, p3.y - 8 - 6, '0' + ( bin2bcd(tm.Second) & 0x0f ) );
    WRITE_SCREEN(); // Send bitmap to display
    delay(wait);
  }

  // -- Show HOUR single digit and SECOND ten's digit
  for ( int x = matrixWidth - 1; x >= 0; x-- ) {
    CLEAR_SCREEN();
    DRAW_LINE(x, 0, matrixWidth - 1 - x, matrixHeight - 1);
    SYNC_DATE_TIME();
    DRAW_CHAR(matrixWidth - x, matrixHeight - CHARACTER_SHAPE_HEIGTH, '0' + ( bin2bcd(tm.Hour) & 0x0f ) );
    DRAW_CHAR( p0.x + x / 2 - 6, p0.y + 6, '0' + ( bin2bcd(tm.Second) >> 4 ) );
    WRITE_SCREEN(); // Send bitmap to display
    delay(wait);
  }

  // -- Show MINUTE ten's digit and SECOND ten's digit
  for ( int y = 0; y < matrixHeight - 1; y++ ) {
    CLEAR_SCREEN();
    DRAW_LINE( matrixWidth - 1, y, 0, matrixHeight - 1 - y );
    SYNC_DATE_TIME();
    DRAW_CHAR( matrixWidth - CHARACTER_SHAPE_WIDTH, y, '0' + ( bin2bcd(tm.Minute) >> 4 ) );
    DRAW_CHAR( p2.x + 8, p2.y - y / 2 - 8 - 10, '0' + ( bin2bcd(tm.Second) >> 4 ) );
    WRITE_SCREEN(); // Send bitmap to display
    delay(wait);
  }

  // -- Show MINUTE single digit and SECOND single digit
  for ( int y = matrixHeight - 1; y >= 0 ; y-- ) {
    CLEAR_SCREEN();
    DRAW_LINE(matrixWidth - 1, y, 0, matrixHeight - 1 - y);
    SYNC_DATE_TIME();
    DRAW_CHAR(0 + CHARACTER_SPACING, matrixHeight - y, '0' + ( bin2bcd(tm.Minute ) & 0x0f ) );
    DRAW_CHAR( p1.x - 8, p1.y + y / 2 + 10 , '0' + ( bin2bcd(tm.Second) & 0x0f ) );
    WRITE_SCREEN(); // Send bitmap to display
    delay(wait);
  }

  wait = wait + inc;
  if ( wait <= LOWER_WAIT_VALUE ) inc = COUNTUP_VALUE;
  if ( wait >  UPPER_WAIT_VALUE ) inc = COUNTDOWN_VALUE;

  SET_SCREEN_INTENSITY(map(wait, LOWER_WAIT_VALUE, UPPER_WAIT_VALUE, 15, 0));
  if (wait <= 12) SET_SCREEN_ROTATION(wait % 4);
}

//////////////////////////////////////////////////////////////////////////////////////////

/* end-of-inotab-file */

