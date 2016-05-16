void setup() {
  Serial.begin(115200);
}

#define START_FREQ    100
#define STOP_FREQ     20000
#define INC_FREQ      1.01
#define NEXT_FREQ     100

void loop() {

#if 0
  for (int freq = 1; freq  < START_FREQ; freq += 1) {
    tone(13, 0);
    delay(1000);
    tone(13, freq);
    Serial.println(freq, DEC);
    delay(5000);
  }
#endif

  for (float freq = START_FREQ; freq  < STOP_FREQ; freq *=INC_FREQ) {
    int freq2 = abs ((sin (freq) + 1.00) * 220);
    tone(13, freq2);
    Serial.print(freq, DEC);
    Serial.print("\t");
    Serial.println(freq2, DEC);
    delay(NEXT_FREQ);
  }

#if 0
  for (int freq = STOP_FREQ; freq > START_FREQ; freq /= INC_FREQ) {
    tone(13, freq);
    Serial.println(freq, DEC);
    delay(NEXT_FREQ);
  }
#endif
}
