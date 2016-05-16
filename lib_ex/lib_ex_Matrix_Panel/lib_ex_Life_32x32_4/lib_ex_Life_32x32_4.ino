//
//      FILE: lib_ex_Spin_B_32x32_3/lib_ex_Spin_B_32x32_3.ino
//    AUTHOR: Thomas Walloschke
//   VERSION: 0.3.4
//   PURPOSE: 32x32 LED Matrix Application (16x8x8 MC) - "Arduino Sketch" - Game of Life
//      DATE: 2016-03-22
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

#include "config.h"       // local - masters all the matrix panel magic...

void setup() {
  setupMatrix();          // 32x32 LED Matrix Panel Basic Setup - cf. config.h
  setupApp();             // Application indiv. setup           - cf. Matrix Panel Functional Frame (below)
}

void loop() {
  loopApp();              // Application indiv. loop            - cf. Matrix Panel Functional Frame (below)
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Matrix Panel Functional Frame
// *****************************

#include <elapsedMillis.h>                    // cf. https://github.com/pfeerick/elapsedMillis/archive/master.zip

#define DELAY                   0             // Sets the time each generation is shown
#define GENESIS_LIFE_TIME       15000         // Sets the interval [ms] after which the genesis phase is over and darkness will come...
#define GENESIS_THRESHOLD       3             // Sets the birth/die threshold
#define MAX_DEATH_THRESHOLD     6             // Sets the maximum die-slowly threshold
#define MAX_BORING_THRESHOLD    7             // Sets the maximum boring threshold

#define SIZEX             MATRIX_PANEL_WIDTH  // Sets the X axis size
#define SIZEY             MATRIX_PANEL_HEIGTH // Sets the Y axis size

#define RANDOM_SEED_PORT        A3            // Sets (floating) analog port for fetching random seed

elapsedMillis genesisLifeTime;                // Elapsed genesis timer

byte world[SIZEX][SIZEY];                     // Creates a buffer world


void setupApp() {

  RESET_SCREEN();                             // Write zeros to screen bitmap and send bitmap to screen

  // -- TBD Say Hello

  delay(2000);                                S// Wait a little

  // -- Seed buffer world randomly
  randomSeed(analogRead(RANDOM_SEED_PORT));   // Seed random generator from analog port (random seed 0...1023)
  seedWorld();                                // Seed the buffer world
}


void loopApp() {

  static byte boring = 0;
  static byte maxNeighbours = MAX_DEATH_THRESHOLD;
  static byte boringThreshold = random(MAX_BORING_THRESHOLD - 2) + 1;

  byte changed = 0;
  byte genesis = (genesisLifeTime < GENESIS_LIFE_TIME ? true : false);

  // -- Birth and death cycle
  for (byte x = 0; x < SIZEX; x++) {
    for (byte y = 0; y < SIZEY; y++) {

      // -- Default is for cell to stay the same
      byte alive = world[x][y];
      DRAW_PIXEL(x, y, alive);

      byte count = neighbours(x, y);
      if (genesis) {
        if (count == GENESIS_THRESHOLD && !alive) {
          // -- A new cell is born
          alive = 1;
          ++changed;

        } else if ((count < GENESIS_THRESHOLD - 1 || count > GENESIS_THRESHOLD ) && alive) {
          // -- Cell dies
          alive = 0;
          ++changed;
        }

      } else {
        if (boring == boringThreshold && count > maxNeighbours) {
          // -- Cell dies
          alive = 0;
          ++changed;
        }
      }
      world[x][y] = alive;
    }
  }

  WRITE_SCREEN();               // Send bitmap to screen

  // -- Watch carefully to ensure something changed...
  if (changed) {
    // -- Time over, darkness will continue to death
    if (boring == boringThreshold) maxNeighbours--;
    boring = 0;                 // hope of one next round

  } else ++boring;              // death may occur

  // -- ...otherwise the display will die out at this point
  if (boring >= MAX_BORING_THRESHOLD ) {
    genesisLifeTime = random(GENESIS_LIFE_TIME);
    boringThreshold = random(MAX_BORING_THRESHOLD - 2) + 1;
    maxNeighbours = MAX_DEATH_THRESHOLD;
    seedWorld();
  }

  delay(DELAY);
}

#define MIN_DENSITY   85
#define MAX_DENSITY   100
//Re-seed
void seedWorld() {
  byte density = MIN_DENSITY + random(MAX_DENSITY - MIN_DENSITY);  //Sets density %
  for ( byte x = 0; x < SIZEX; x++ ) {
    for ( byte y = 0; y < SIZEY; y++ ) {
      if ( random(100) > density )
        world[x][y] = 1;
      else
        world[x][y] = 0;
    }
  }
}

/**
   Runs the rule checks, including screen wrap

             -1     y    +1
          -+-----+-----+-----+-
      -1   |  G  |  D  |  F  |
          -+-----+-----+-----+-
       x   |  C  |  X  |  A |
          -+-----+-----+-----+-
      +1   |  H  |  B  |  E  |
          -+-----+-----+-----+-

   Result: 0..8
*/
byte neighbours(byte x, byte y) {
  return
    world[(x + 1) % SIZEX][y] +                                // A
    world[x][(y + 1) % SIZEY] +                                // B

    world[(x + SIZEX - 1) % SIZEX][y] +                        // C
    world[x][(y + SIZEY - 1) % SIZEY] +                        // D

    world[(x + 1) % SIZEX][(y + 1) % SIZEY] +                  // E
    world[(x + SIZEX - 1) % SIZEX][(y + 1) % SIZEY] +          // F

    world[(x + SIZEX - 1) % SIZEX][(y + SIZEY - 1) % SIZEY] +  // G
    world[(x + 1) % SIZEX][(y + SIZEY - 1) % SIZEY];           // H
}

