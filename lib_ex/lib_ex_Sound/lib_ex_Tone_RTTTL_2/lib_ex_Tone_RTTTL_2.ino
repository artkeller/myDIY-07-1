// A fun sketch to demonstrate the use of the Tone library.

// To mix the output of the signals to output to a small speaker (i.e. 8 Ohms or higher),
// simply use 1K Ohm resistors from each output pin and tie them together at the speaker.
// Don't forget to connect the other side of the speaker to ground!

// You can get more RTTTL (RingTone Text Transfer Language) songs from
// http://code.google.com/p/rogue-code/wiki/ToneLibraryDocumentation

#include <Tone.h>

Tone tone1;

#define OCTAVE_OFFSET 0

int notes[] = { 0,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

//char *song = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
//char *song = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
//char *song = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
//char *song = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
//char *song = "Muppets:d=4,o=5,b=250:c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,8a,8p,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,8e,8p,8e,g,2p,c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,a,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,d,8d,c";
//char *song = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
//char *song = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
//char *song = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";
//char *song = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
//char *song = "MASH:d=8,o=5,b=140:4a,4g,f#,g,p,f#,p,g,p,f#,p,2e.,p,f#,e,4f#,e,f#,p,e,p,4d.,p,f#,4e,d,e,p,d,p,e,p,d,p,2c#.,p,d,c#,4d,c#,d,p,e,p,4f#,p,a,p,4b,a,b,p,a,p,b,p,2a.,4p,a,b,a,4b,a,b,p,2a.,a,4f#,a,b,p,d6,p,4e.6,d6,b,p,a,p,2b";
//char *song = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
//char *song = "GoodBad:d=4,o=5,b=56:32p,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,d#,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,c#6,32a#,32d#6,32a#,32d#6,8a#.,16f#.,32f.,32d#.,c#,32a#,32d#6,32a#,32d#6,8a#.,16g#.,d#";
//char *song = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
//char *song = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
//char *song = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
//char *song = "Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#";
//char *song = "Gadget:d=16,o=5,b=50:32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,32d#,32f,32f#,32g#,a#,d#6,4d6,32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,8d#";
//char *song = "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";
//char *song = "MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.";
//char *song = "LeisureSuit:d=16,o=6,b=56:f.5,f#.5,g.5,g#5,32a#5,f5,g#.5,a#.5,32f5,g#5,32a#5,g#5,8c#.,a#5,32c#,a5,a#.5,c#.,32a5,a#5,32c#,d#,8e,c#.,f.,f.,f.,f.,f,32e,d#,8d,a#.5,e,32f,e,32f,c#,d#.,c#";
//char *song = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
//char *song = "AbbaMo:d=4,o=6,b=112:8e7,8e7,8e7,8e7,8e7,8e7,16e,16a,16c7,16e7,8d#7,8d#7,8d#7,8d#7,8d#7,8d#7,16f,16a,16c7,16d#7,d7,8c7,8a,8c7,c7,2a,32a,32c7,32e7,8a7";
//char *song = "Beethoven:d=4,o=6,b=80:16g5,16g5,16g5,d#5,16f5,16f5,16f5,d5,16g5,16g5,16g5,16d#5,16g#5,16g#5,16g#5,16g5,16d#,16d#,16d#,c,16g5,16g5,16g5,16d5,16g#5,16g#5,16g#5,16g5,16f,16f,16f,d";
//char *song = "GunsAndR:d=4,o=6,b=225:d5,d,a5,g5,g,a5,f#,d5,d,a5,g5,g,a5,f#,a5,e5,d,a5,g,a5,f#,a5,e5,d,a5,g5,g,a5,f#,a5,f#,a5,e5,d,a5,g5,g,a5,f#,a5";
//char *song = "Temptation:d=4,o=6,b=112:f5,16p,32p,8g5,8a5,8c,8d,8f,f5,8p,8g5,8a5,8c,8d,8f,8f5,c5,16p,32p,8c5,8d5,f5,g5,8p,16p,16f5,16d5,8f5,p,8a5,8g5";
//char *song = "DeepPurpl:d=4,o=6,b=112:c5,d#5,f.5,c5,d#5,8f#5,f5,p,c5,d#5,f.5,d#5,c5,2p,8p,c5,d#5,f.5,c5,d#5,8f#5,f5,p,c5,d#5,f.5,d#5,c5,p";
//char *song = "LionKing:d=4,o=6,b=225:8c,8d#,p,8d#,8p,8d#,8d,8p,2c,2p,a5,8c,8d#,8p,8d#,8p,d#,1c,p,8p,8c,8d#,p,8d#,8p,8d#,8d,8p,1c,8p,a5,8p,c,8p,d#,8p,d,8p,1d,2p,8e,8g,p,8g,p,8a,p,2a,2p,a,p,g,8p,8d#,8p,8d,c,1d";
//char *song = "Deeppurpl:d=4,o=6,b=125:8e5,8p,p,2g,2f#,e,8d5,8p,8e5,8p,p,2g,2f#,e,8c5,8p,8d5,8p,p,2f#,8d5,8e,d,8d5,8p,8d5,8p,8e5,8p,p,e.,8d,2b5,8d5,8p,8d5,8p,8e5,8p,p,2g,2f#,e,8d5,8p,8e5,8p,p,2g,2f#,e,8c5,8p,8d5,8p,p,2f#,8d5,8e,d,8d5,8p,8d5,8p,8e5,8p,p,e.,8d,2b5,8d5,8p,8d5,8p,2e5";
//char *song = "Metallica:d=4,o=6,b=125:a5,8a,8c7,8d#,d,8a,a5,8a,8c7,8d#,d,8a,a5,8a,8c7,8d#,d,8a,a5,8a,8c7,8d#,d,8a,a5";
//char *song = "DJDorusd:d=4,o=6,b=140:f.,16p,8f,8f,8g,8f,8e,d.,8p,d.,8p,8e,8e,8f,g.,32p,8f,8g,a,a,8g,8c.,16p";
//char *song = "lamourto:d=4,o=6,b=80:8e5,8p,8e5,16e5,16c,8b5,8p,8b5,16b5,16c,8a5,8p,16a5,16g5,8a5,8a5,16a5,16g5,16a5,16g5,8e5,8p,8e5,16e5,16c,8b5,8p,8b5,16b5,16c,8a5,8p,8a5,16a5,16g5,a5";
//char *song = "LeeCarbre:d=4,o=6,b=112:8c,8b5,8a5,16b5,16c,16p,8b5,16a5,16p,16a5,16b5,16a5,8c,8b5,8a5,16b5,16c,16p,8b5,16a5,16p,16a5,16b5,16a5,8c,8b5,8a5,16b5,16c,16p,8b5,16a5,16p,16a5,16b5,16a5,8c,8b5,8a5,16b5,16c,16p,8b5,16a5,16p,16a5,16b5,16a5,8c,8b5,8a5,16b5,16c,16p,8b5,16a5,16p,16a5,16b5,16a5,8c,8b5,8a5,16b5,16c,16p,8b5,16a5,16p,16a5,16b5,16a5";
//char *song = "Overmyhe:d=4,o=6,b=180:8d5,8d5,8f5,8d5,8a5,8f5,8a5,8f5,8e5,8e5,8g5,8e5,8c5,8c5,8e5,8c5,8d5,8d5,8f5,8d5,8a5,8f5,8a5,8f5,8e5,8e5,8g5,8e5,8c5,8c5,8e5,8c5";
//char *song = "asikveyse:d=4,o=6,b=70:16b5,16c,8c,8c,16c,8b5,16a5,16c,16b5,8b5,16b5,8a5,16g5,8a5,8a5,16a5,16g5,16g5,16f5,16a5,16g5,8g5,16g5,16f5,16f5,16d5,16g5,16e5,8f5,16f5,8e5,16d5,16f5,16e5,8e5,16e5,8d5,16c5,16e5,16d5,8d5,8d5,16d5,16d5,16d5,16d5";
//char *song = "BoboMarle:d=4,o=6,b=100:a5,8g#5,8a5,8g#5,2f#5,2p,8c#,16p,32p,8d,8c#,8b5,2a5,2p,8a5,8p,8g#5,8a5,8g#5,1f#5,8p,16p,8c#,8p,8d,8c#,8b5,2a5,p";
char *song = "Destinys:d=4,o=6,b=125:8f#5,8b5,8f#,8e,8d,8c#,8d,2b.5,p,8p,8f#5,8b5,8f#,8e,8d,8c#,8d,8e.,8d.,2b.5,8f#5,8e5,8p,8e5,8b5,8f#,8e,8d,8b5,8d,8e,8e,8c#,8c#,8a#5,8a#5,8f#5,8f#5,8d,16d.,8b5,16b.5,8f#5,8e5,8f#5,8e5,8e5,8c#,8c#,8c#,8c#,8c#,8d,8e,8d,8p,8f#5,8b5,8f#,8e,8d,8c#,8d,2b.5,p,8p,8f#5,8b5,8f#,8e,8d,8c#,8d,8e.,8d.,2b.5";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";
//char *song = "";

// _____________

void setup(void)
{
  Serial.begin(115200);
  tone1.begin(13);
}

#define isdigit(n) (n >= '0' && n <= '9')

void play_rtttl(char *p)
{
  // Absolutely no error checking in here

  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd')
  {
    p++; p++;              // skip "d="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }

  Serial.print("ddur: "); Serial.println(default_dur, 10);

  // get default octave
  if(*p == 'o')
  {
    p++; p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }

  Serial.print("doct: "); Serial.println(default_oct, 10);

  // get BPM
  if(*p == 'b')
  {
    p++; p++;              // skip "b="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

  Serial.print("bpm: "); Serial.println(bpm, 10);

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  Serial.print("wn: "); Serial.println(wholenote, 10);


  // now begin note loop
  while(*p)
  {
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch(*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.')
    {
      duration += duration/2;
      p++;
    }
  
    // now, get scale
    if(isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if(note)
    {
      Serial.print("Playing: ");
      Serial.print(scale, 10); Serial.print(' ');
      Serial.print(note, 10); Serial.print(" (");
      Serial.print(notes[(scale - 4) * 12 + note], 10);
      Serial.print(") ");
      Serial.println(duration, 10);
      tone1.play(notes[(scale - 4) * 12 + note]);
      delay(duration);
      tone1.stop();
    }
    else
    {
      Serial.print("Pausing: ");
      Serial.println(duration, 10);
      delay(duration);
    }
  }
}

void loop(void)
{
  play_rtttl(song);
  Serial.println("Done.");
  while(1);
}
