/*
  Melody

  Plays a melody

  circuit:
   8-ohm speaker on digital pin 13

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone

  modified 21 March 2016
  by Thomas Walloschke
*/

#include "melodies.h"

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = PAUSE; thisNote < MELODY_NOTES; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = MELODY_SPEED / MELODY_ID[1][thisNote];
    tone(13, MELODY_ID[0][thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.25;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    // noTone(13);
  }
}

void loop() {
  // no need to repeat the melody.
}
