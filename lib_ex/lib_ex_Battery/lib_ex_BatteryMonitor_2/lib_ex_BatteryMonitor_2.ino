#include <Battery.h>

/**
 * Change in battery.h
 * to
 * 
 *  uint16_t reading = (analogRead(sensePin) * dividerRatio * refVoltage)/1023;
 */

Battery battery(2000, 3000, A0);  // low=2.000V, nominal=3.000V

void setup() {
	Serial.begin(115200);
	while (!Serial);
	battery.begin(5000,1);          // refVoltage=5.000V, ratio=1
}

void loop() {
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	delay(500);

	Serial.print("Battery voltage is ");
	Serial.print(battery.voltage());
	Serial.print(" (");
	Serial.print(battery.level());
	Serial.println(")");
}
