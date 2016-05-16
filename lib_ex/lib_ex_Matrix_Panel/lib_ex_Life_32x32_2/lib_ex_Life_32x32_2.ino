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

#include <elapsedMillis.h>
elapsedMillis timetoReseed;
elapsedMillis genesisLifeTime;

#define DELAY           0                     // Sets the time each generation is shown
//#define RESEEDRATE      30000                 // Sets the rate the world is re-seeded
//#define RESEEDINTERVAL  20000                 // Sets the interval after which the world is re-seeded
#define GENESISINTERVAL 30000                 // Sets the interval after which the genesis is over
#define THRESHOLD       3                     // Sets the birth/die threshold
#define SIZEX           32                    // Sets the X axis size
#define SIZEY           32                    // Sets the Y axis size
byte world[1][SIZEX][SIZEY];                  // Creates a single buffer world
int geck = 0;                                 // Counter for re-seeding

void _setup() {
  randomSeed(analogRead(5));
  seedWorld();
  
  matrix.fillScreen(LOW);
  matrix.write(); // Send bitmap to display

  delay(1000);
}

void loop() {
#if 1
  static byte boring = 0;
#endif
  byte changed = 0;
  byte genesis = (genesisLifeTime < GENESISINTERVAL ? true : false);

  // Birth and death cycle
  for (byte x = 0; x < SIZEX; x++) {
    for (byte y = 0; y < SIZEY; y++) {

      // Default is for cell to stay the same
      byte alive = world[0][x][y];
      matrix.drawPixel(x, y, alive);

      byte count = neighbours(x, y);
      if (count == THRESHOLD && !alive && genesis) {
        // A new cell is born
        alive = 1;
        ++changed;
      } else if ((count < THRESHOLD - 1 || count > THRESHOLD || (changed == 0 and not genesis)) && alive ) {
        // Cell dies
        alive = 0;
        ++changed;
      }
      world[0][x][y] = alive;
    }
  }

  matrix.write(); // Send bitmap to display

#if 0
  // Copy next generation into place
  for (byte x = 0; x < SIZEX; x++) {
    for (byte y = 0; y < SIZEY; y++) {
      world[0][x][y] = world[0][x][y];
    }
  }
#endif

  if (changed)   boring = 0;
  else           ++boring;

  //Otherwise the display will die out at some point
  if (boring >= 5 
  //|| ++geck > RESEEDRATE
  ) {
  //  geck = 0;
    genesisLifeTime = random(GENESISINTERVAL);
    seedWorld();
  }

#if 0
  //Counts and then checks for re-seeding
  if (timetoReseed > RESEEDINTERVAL)  {
    timetoReseed = 0;
    seedWorld();
  }
#endif

  delay(DELAY);
}

#define MIN_DENSITY   30
//Re-seeds based off of RESEEDRATE
void seedWorld() {
  byte density = MIN_DENSITY + random(100-MIN_DENSITY);    //Sets density %
  for ( byte x = 0; x < SIZEX; x++ ) {
    for ( byte y = 0; y < SIZEY; y++ ) {
      if ( random(100) < density )
        world[0][x][y] = 1;
      else
        world[0][x][y] = 0;
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
    world[0][(x + 1) % SIZEX][y] +                                // A
    world[0][x][(y + 1) % SIZEY] +                                // B

    world[0][(x + SIZEX - 1) % SIZEX][y] +                        // C
    world[0][x][(y + SIZEY - 1) % SIZEY] +                        // D

    world[0][(x + 1) % SIZEX][(y + 1) % SIZEY] +                  // E
    world[0][(x + SIZEX - 1) % SIZEX][(y + 1) % SIZEY] +          // F

    world[0][(x + SIZEX - 1) % SIZEX][(y + SIZEY - 1) % SIZEY] +  // G
    world[0][(x + 1) % SIZEX][(y + SIZEY - 1) % SIZEY];           // H
}

