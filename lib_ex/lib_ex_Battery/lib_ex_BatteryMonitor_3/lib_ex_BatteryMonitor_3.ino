#include <Battery.h>

/**
 * Change in battery.h
 * to
 * 
 *  uint16_t reading = (analogRead(sensePin) * dividerRatio * refVoltage)/1023;
 */

// cf. http://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/

#define Vcc1              4.545                                 // per voltmeter
#define Vcc2              4.525                                 // per readVcc() function
#define INTERNAL11REF     1.1 * Vcc1 / Vcc2                     // adjusted internal 1.1V reference
#define SCALE_CONSTANT    long(INTERNAL11REF * 1023.0 * 1000.0) // 1125300 = 1.1*1023*1000

// -- Battery Constructor
Battery battery(2000, 3000, A0);  // low=2.000V, nominal=3.000V, Read A0

long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  

  delay(2);                         // wait for Vref to settle
  ADCSRA |= _BV(ADSC);              // Start conversion
  while (bit_is_set(ADCSRA,ADSC));  // measuring

  uint8_t low  = ADCL;              // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH;              // unlocks both
  long result = (high<<8) | low;

  result = SCALE_CONSTANT / result; // calculate Vcc (in mV)
  return result;                    // Vcc in millivolts
}

void setup() {
	Serial.begin(115200);
	while (!Serial);

}

void loop() {
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	delay(500);

  int Vcc = readVcc();
  battery.begin(Vcc,1);                   // refVoltage=recentVcc, ResistorRatio=1

	Serial.print("Battery voltage is ");
	Serial.print(battery.voltage());
	Serial.print("mV (");
	Serial.print(battery.level());
	Serial.print("%) @Vcc ");
  Serial.print(battery.level());
  Serial.print("mv");

}
