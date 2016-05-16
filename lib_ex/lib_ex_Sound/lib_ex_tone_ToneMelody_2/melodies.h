#include "pitches.h"

#define MELODY_SPEED   1100          // default 1000

#define MELODY_ID1     melody1
#define MELODY_NOTES1  8
#define MELODY_ID2     melody2
#define MELODY_NOTES2  30
#define MELODY_ID3     melody3
#define MELODY_NOTES3  78
#define MELODY_ID4     melody4
#define MELODY_NOTES4  59
#define MELODY_ID5     melody5
#define MELODY_NOTES5  68
#define MELODY_ID6     melody6
#define MELODY_NOTES6  126
#define MELODY_ID7     melody7
#define MELODY_NOTES7  28
#define MELODY_ID8     melody8
#define MELODY_NOTES8  40
#define MELODY_ID9     melody9
#define MELODY_NOTES9  73

#define MELODY_ID      MELODY_ID9
#define MELODY_NOTES   MELODY_NOTES9


#if MELODY_ID  == MELODY_ID1
int melody1[][MELODY_NOTES1] = {
  // notes in the melody:
  {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3,
    NOTE_G3, PAUSE, NOTE_B3, NOTE_C4
  },
  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  {
    4, 8, 8, 4,
    4, 4, 4, 4
  }
};
#endif

#if MELODY_ID  == MELODY_ID2
int melody2[][MELODY_NOTES2] = {
  // --
  { NOTE_C4, PAUSE, NOTE_D4, PAUSE, NOTE_F4, PAUSE,
    NOTE_D4, PAUSE, NOTE_F4, PAUSE, NOTE_G4, PAUSE,
    NOTE_F4, PAUSE, NOTE_G4, PAUSE, NOTE_A4, PAUSE,
    NOTE_G4, PAUSE, NOTE_A4, PAUSE, NOTE_B4, PAUSE,
    NOTE_A4, PAUSE, NOTE_B4, PAUSE, NOTE_C5, PAUSE
  },
  { 8, 16, 8, 16, 8, 4,
    8, 16, 8, 16, 8, 4,
    8, 16, 8, 16, 8, 4,
    8, 16, 8, 16, 8, 4,
    8, 16, 8, 16, 8, 4
  }
};
#endif

#if MELODY_ID  == MELODY_ID3
int melody3[][MELODY_NOTES3] = {
  // -- Mario Bros Tunes main theme melody
  {
    NOTE_E7, NOTE_E7, PAUSE, NOTE_E7,
    PAUSE, NOTE_C7, NOTE_E7, PAUSE,
    NOTE_G7, PAUSE, PAUSE,  PAUSE,
    NOTE_G6, PAUSE, PAUSE, PAUSE,

    NOTE_C7, PAUSE, PAUSE, NOTE_G6,
    PAUSE, PAUSE, NOTE_E6, PAUSE,
    PAUSE, NOTE_A6, PAUSE, NOTE_B6,
    PAUSE, NOTE_AS6, NOTE_A6, PAUSE,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, PAUSE, NOTE_F7, NOTE_G7,
    PAUSE, NOTE_E7, PAUSE, NOTE_C7,
    NOTE_D7, NOTE_B6, PAUSE, PAUSE,

    NOTE_C7, PAUSE, PAUSE, NOTE_G6,
    PAUSE, PAUSE, NOTE_E6, PAUSE,
    PAUSE, NOTE_A6, PAUSE, NOTE_B6,
    PAUSE, NOTE_AS6, NOTE_A6, PAUSE,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, PAUSE, NOTE_F7, NOTE_G7,
    PAUSE, NOTE_E7, PAUSE, NOTE_C7,
    NOTE_D7, NOTE_B6, PAUSE, PAUSE
  },
  {
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    9, 9, 9,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    9, 9, 9,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
  }
};
#endif

#if MELODY_ID  == MELODY_ID4
int melody4[][MELODY_NOTES4] = {
  {
    // Tetris - Sopran
    NOTE_E3, NOTE_H2, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_D3, NOTE_C3, NOTE_H2,
    NOTE_A2, NOTE_A2, NOTE_C3, NOTE_E3, NOTE_D3, NOTE_C3,
    NOTE_H2, NOTE_H2, NOTE_C3, NOTE_D3, NOTE_E3,
    NOTE_C3, NOTE_A2, NOTE_A2,
    PAUSE, NOTE_D3, NOTE_F3, NOTE_A3, NOTE_G3, NOTE_F3,
    NOTE_E3, NOTE_E3, NOTE_C3, NOTE_E3, NOTE_D3, NOTE_C3,
    NOTE_H2, NOTE_H2, NOTE_C3, NOTE_D3, NOTE_E3,
    NOTE_C3, NOTE_A2, NOTE_A2, PAUSE,
    NOTE_E2, NOTE_C2, NOTE_D2, NOTE_H1, NOTE_C2, NOTE_A1, NOTE_GS1, NOTE_H1,
    NOTE_E2, NOTE_C2, NOTE_D2, NOTE_H1, NOTE_C2, NOTE_E2, NOTE_A2, NOTE_GS2
  },
  {
    4, 8, 8, 8, 16, 16, 8, 8,
    4, 8, 8, 4, 8, 8,
    4, 8, 8, 4, 4,
    4, 4, 2,
    8, 4, 8, 4, 8, 8,
    4, 8, 8, 4, 8, 8,
    4, 8, 8, 4, 4,
    4, 4, 4, 4,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 4, 4, 2, 1
  }
};
#endif

#if MELODY_ID  == MELODY_ID5
int melody5[][MELODY_NOTES5] = {
  {
    // Tetris-Alt
    NOTE_H2, NOTE_GS2, NOTE_A2, NOTE_H2, NOTE_E3, NOTE_D3, NOTE_A2, NOTE_GS2,
    NOTE_E2, NOTE_E2, NOTE_A2, NOTE_C3, NOTE_H2, NOTE_A2,
    NOTE_GS2, NOTE_E2, NOTE_GS2, NOTE_A2, NOTE_H2, NOTE_C3,
    NOTE_A2, NOTE_E2, NOTE_E2,
    PAUSE, NOTE_F2, NOTE_A2, NOTE_C3, NOTE_C3, NOTE_C3, NOTE_H2, NOTE_A2,
    NOTE_G2, NOTE_G2, NOTE_E2, NOTE_G2, NOTE_A2, NOTE_G2, NOTE_F2, NOTE_E2,
    NOTE_GS2, NOTE_E2, NOTE_GS2, NOTE_A2, NOTE_H2, NOTE_GS2, NOTE_C3, NOTE_GS2,
    NOTE_A2, NOTE_E2, NOTE_E2, NOTE_E2, PAUSE,
    NOTE_C2, NOTE_A1, NOTE_H1, NOTE_GS1, NOTE_A1, NOTE_E1, NOTE_E1, NOTE_G1,
    NOTE_C2, NOTE_A1, NOTE_H1, NOTE_GS1, NOTE_A1, NOTE_C2, NOTE_E2, NOTE_E2
  },
  {
    4, 8, 8, 8, 16, 16, 8, 8,
    4, 8, 8, 4, 8, 8,
    8, 8, 8, 8, 4, 4,
    4, 4, 2,
    8, 4, 8, 8, 16, 16, 8, 8,
    4, 8, 8, 8, 16, 16, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 4, 4, 4,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 4, 4, 2, 1
  }
};
#endif

#if MELODY_ID  == MELODY_ID6
int melody6[][MELODY_NOTES6] = {
  {
    // Tetris - Bass
    NOTE_E1, NOTE_E2, NOTE_E1, NOTE_E2, NOTE_E1, NOTE_E2, NOTE_E1, NOTE_E2,
    NOTE_A1, NOTE_A2, NOTE_A1, NOTE_A2, NOTE_A1, NOTE_A2, NOTE_A1, NOTE_A2,
    NOTE_GS1, NOTE_GS2, NOTE_GS1, NOTE_GS2, NOTE_GS1, NOTE_GS2, NOTE_GS1, NOTE_GS2,
    NOTE_A1, NOTE_A2, NOTE_A1, NOTE_A2, NOTE_A1, NOTE_A2, NOTE_H1, NOTE_C2,
    NOTE_D2, NOTE_D1, PAUSE, NOTE_D1, PAUSE, NOTE_D1, NOTE_A1, NOTE_F1,
    NOTE_C1, NOTE_C2, PAUSE, NOTE_C2, NOTE_C1, NOTE_G1, PAUSE, NOTE_G1,
    NOTE_H1, NOTE_H2, PAUSE, NOTE_H2, PAUSE, NOTE_E2, PAUSE, NOTE_GS2,
    NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2, NOTE_A1, PAUSE,
    NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2,
    NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2,
    NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2,
    NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2,
    NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2,
    NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2,
    NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2, NOTE_A1, NOTE_E2,
    NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2, NOTE_GS1, NOTE_E2
  },
  {
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 4, 4,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
  }
};
#endif

#if MELODY_ID  == MELODY_ID7
int melody7[][MELODY_NOTES7] = {
  {
    NOTE_G6, NOTE_G6, NOTE_A6, NOTE_G6, NOTE_C7, NOTE_B6, PAUSE,
    NOTE_G6, NOTE_G6, NOTE_A6, NOTE_G6, NOTE_D7, NOTE_C7, PAUSE,
    NOTE_G6, NOTE_G6, NOTE_G7, NOTE_E7, NOTE_C7, NOTE_B6, NOTE_A6, PAUSE,
    NOTE_F7, NOTE_F7, NOTE_E7, NOTE_C7, NOTE_D7, NOTE_C7
  },
  {
    8, 8, 4, 4, 4, 2, 4,
    8, 8, 4, 4, 4, 2, 4,
    8, 8, 4, 4, 4, 4, 4, 4,
    8, 8, 4, 4, 4, 2
  }
};
#endif

#if MELODY_ID  == MELODY_ID8
int melody8[][MELODY_NOTES8] = {
  // Morgen kommt der Weihnachtsmann
  {
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4,
    NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
    NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4
  },
  {
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4, 2, 2,
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4, 2, 2,
  }
};
#endif

#if MELODY_ID  == MELODY_ID9
int melody9[][MELODY_NOTES9] = {
  // Mission Impossible
  {
    NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, 
    NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, 
    NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, 
    NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_G5, // Upswing 5

    NOTE_G2, NOTE_G2, NOTE_AS2, NOTE_C3, NOTE_G2, NOTE_G2, NOTE_F2,  NOTE_FS2,
    NOTE_G2, NOTE_G2, NOTE_AS2, NOTE_C3, NOTE_G2, NOTE_G2, NOTE_F2,  NOTE_FS2,

    NOTE_G2, NOTE_G2, NOTE_AS2, NOTE_C3, NOTE_G2, NOTE_G2, NOTE_F2,  NOTE_FS2,
    NOTE_G2, NOTE_G2, NOTE_AS2, NOTE_C3, NOTE_G2, NOTE_G2, NOTE_F2,  NOTE_FS2,

    NOTE_G2
  },
  {
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16,

    2, 2, 4, 4, 2, 2, 4, 4,       //2000
    2, 2, 4, 4, 2, 2, 4, 4,

    2, 2, 4, 4, 2, 2, 4, 4,       //2000
    2, 2, 4, 4, 2, 2, 4, 4,

    2
  }
};
#endif
