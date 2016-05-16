//
//      FILE: lib_ex_Spin_B_32x32_3/lib_ex_Spin_B_32x32_3.ino
//    AUTHOR: Thomas Walloschke
//   VERSION: 0.3.2
//   PURPOSE: 32x32 LED Matrix Application (16x8x8 MC) - "Arduino Sketch" - Game of Life
//      DATE: 2016-03-15
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

#include <elapsedMillis.h>
elapsedMillis timetoReseed;
elapsedMillis genesisLifeTime;

#define DELAY           0                     // Sets the time each generation is shown
#define RESEEDRATE      30000                 // Sets the rate the world is re-seeded
#define RESEEDINTERVAL  30000                 // Sets the interval after which the world is re-seeded
#define GENESISINTERVAL 30000                 // Sets the interval after which the genesis is over
#define THRESHOLD       3                     // Sets the birth/die threshold
#define SIZEX           32                    // Sets the X axis size
#define SIZEY           32                    // Sets the Y axis size
byte world[SIZEX][SIZEY];                     // Creates a buffer world

void setupApp() {
  randomSeed(analogRead(2));
  seedWorld();

  CLEAR_SCREEN();
  WRITE_SCREEN();                             // Send bitmap to screen

  delay(1000);
}

void loopApp() {
  
  static byte boring = 0;

  byte changed = 0;
  byte genesis = (genesisLifeTime < GENESISINTERVAL ? true : false);

  // -- Birth and death cycle
  for (byte x = 0; x < SIZEX; x++) {
    for (byte y = 0; y < SIZEY; y++) {

      // -- Default is for cell to stay the same
      byte alive = world[x][y];
      DRAW_PIXEL(x, y, alive);

      byte count = neighbours(x, y);
      if (count == THRESHOLD && !alive && genesis) {
        
        // -- A new cell is born
        alive = 1;
        ++changed;
      } else if ((count < THRESHOLD - 1 || count > THRESHOLD || (changed == 0 and not genesis)) && alive ) {
        
        // -- Cell dies
        alive = 0;
        ++changed;
      }
      world[x][y] = alive;
    }
  }

  WRITE_SCREEN();               // Send bitmap to screen

  if (changed)   boring = 0;
  else           ++boring;

  // -- Otherwise the display will die out at some point
  if (boring >= 5 ) {
    genesisLifeTime = random(GENESISINTERVAL);
    timetoReseed = 0;
    seedWorld();
  }

  // -- Counts and then checks for re-seeding
  if (timetoReseed > RESEEDINTERVAL)  {
    timetoReseed = 0;
    seedWorld();
  }

  delay(DELAY);
}

#define MIN_DENSITY   70
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

