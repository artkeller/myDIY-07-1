//
//      FILE: lib_ex_TEMPLATE_32x32/lib_ex_TEMPLATE_32x32.ino
//    AUTHOR: Thomas Walloschke
//   VERSION: 0.1.0
//   PURPOSE: 32x32 LED Matrix Application (16 x 8x8 MC) - "Arduino Sketch" - <TEMPLATE>
//      DATE: 2016-MM-DD
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
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Matrix Panel Functional Frame
// *****************************

// -- Blink-Test (Demo)
void setupApp () {
  SET_SCREEN_INTENSITY(8);
  while (1) {
    RESET_SCREEN();
    delay(1000);
    TEST_SCREEN();
    delay(1000);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

/* end-of-inotab-file */

