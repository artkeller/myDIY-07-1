#include <VoltageReference.h>

#define SERIAL_MONITOR            true                                // Serial monitor or plotter

// -- Internal reference calibration
#define Vcc1                      4577                                // to be determined by external measurment 
#define Vcc2                      4508                                // to be determined by readVcc()
#define INTERNAL11REF             long(1.1 * Vcc1 / Vcc2 * 1000000L)  // calibrated internal 1.1V reference 

// -- Battery values
#define CR2032_NOMINAL_MV         3000                                // nominal voltage of backup battery CR2032 in mV                 
#define CR2032_MINIMAL_MV         2000                                // mininal voltage of backup battery CR2032 in mV
#define CAPACITY_NOMINAL_PERC     100                                 // nomimal capacity means 100%
#define CAPACITY_MIMIMAL_PERC     0                                   // minimal capacity means 0%                
#define CR2032_CAPACITY(voltage)  map(voltage,CR2032_NOMINAL_MV,CR2032_MINIMAL_MV,CAPACITY_NOMINAL_PERC,CAPACITY_MIMIMAL_PERC)

// -- Create vRef object
VoltageReference vRef;

// -- Calibrate
void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Calibrating voltage reference");
  vRef.begin(INTERNAL11REF);
}

void loop() {

  // -- Wait 1s
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);

  // -- Read values
  int vcc           = vRef.readVcc();
  int internal      = vRef.internalValue();
  long calibration  = vRef.calibrate(Vcc1);
  int battery        = int((float)analogRead(A0) / 1023.0 * vcc);

  // -- Print values
#if SERIAL_MONITOR
  Serial.print("Vcc voltage is ");
  Serial.print(vcc, DEC);
  Serial.print("mV, battery voltage is ");
  Serial.print(battery, DEC);
  Serial.print("mV (");
  Serial.print(BATTERY_CAPACITY(battery), DEC);
  Serial.print("%), internal voltage is ");
  Serial.print(internal, DEC);
  Serial.print("mv, calibration value is ");
  Serial.print(calibration, DEC);
  Serial.println();
#else /* SERIAL_PLOTTER */
  Serial.print(vcc);
  Serial.print("\t");
  Serial.print(battery);
  Serial.print("\t");
  Serial.print(BATTERY_CAPACITY(battery));
  Serial.print("\t");
  Serial.print(internal);
  Serial.print("\t");
  Serial.print(calibration);
  Serial.println();
#endif /* SERIAL_MONITOR */
}
