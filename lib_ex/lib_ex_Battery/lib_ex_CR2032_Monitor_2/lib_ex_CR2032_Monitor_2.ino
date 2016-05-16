#include <VoltageReference.h>

#define SERIAL_MONITOR            true                                // Serial monitor or plotter
#define SERIAL_SPEED              115200                              // Serial speed

// -- Internal reference calibration
#define Vcc1                      4577                                // Vcc [mV] to be determined by external measurment
#define Vcc2                      4508                                // Vcc [mV] to be determined by readVcc()
#define INTERNAL11REF             long(1.1 * 1000000L * Vcc1 / Vcc2)  // calibrated internal 1.1V reference 

// -- Battery values
#define CR2032_NOMINAL_MV         3000                                // nominal voltage [mV] of backup battery CR2032                 
#define CR2032_MINIMAL_MV         2000                                // mininal voltage [mV] of backup battery CR2032
#define CAPACITY_NOMINAL_PERC     100                                 // nomimal capacity defines typ. 100%
#define CAPACITY_MIMIMAL_PERC     0                                   // minimal capacity defines typ. 0%                
#define CAPACITY(voltage)         map(voltage,CR2032_NOMINAL_MV,CR2032_MINIMAL_MV,CAPACITY_NOMINAL_PERC,CAPACITY_MIMIMAL_PERC)

// -- Create vRef object
VoltageReference vRef;

// -- Calibrate vRef
void setup() {
  Serial.begin(SERIAL_SPEED);
  while (!Serial);

#if SERIAL_MONITOR
  Serial.print(F("Calibrating voltage reference ("));
  Serial.print(INTERNAL11REF);
  Serial.println(F(")"));
#endif

  vRef.begin(INTERNAL11REF);
  
#if SERIAL_MONITOR
  Serial.println(F("Measurements..."));
#endif
}

void loop() {

  // -- Wait 1s
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);

  // -- Read values
  int vcc           = vRef.readVcc();
  int battery       = int((float)analogRead(A0) / 1023.0 * vcc);
  
  int internal      = vRef.internalValue();
  long calibration  = vRef.calibrate(Vcc1);

  // -- Print values
#if SERIAL_MONITOR
  Serial.print(F("Vcc voltage is "));           Serial.print(vcc, DEC);
  Serial.print(F("mV, battery voltage is "));   Serial.print(battery, DEC);
  Serial.print(F("mV ("));                      Serial.print(CAPACITY(battery), DEC);
  Serial.print(F("%), internal voltage is "));  Serial.print(internal, DEC);
  Serial.print(F("mv, calibration value is ")); Serial.print(calibration, DEC);
  Serial.println();
#else /* SERIAL_PLOTTER */
  Serial.print(vcc);                            Serial.print(F("\t"));
  Serial.print(battery);                        Serial.print(F("\t"));
  Serial.print(CAPACITY(battery));              Serial.print(F("\t"));
  Serial.print(internal);                       Serial.print(F("\t"));
  Serial.print(calibration);                    Serial.println();
#endif /* SERIAL_MONITOR */
}
