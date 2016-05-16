#include <OneWire.h>

// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire  ds(2);  // on pin 10 (a 4.7K resistor to VCC is necessary)
const int sensorROMRegistry[][9] = {

  // Registry Data
  //Type   ------- ID (48bits) ------------  CRC8  CAL


  {0x28, 0xFF, 0xA2, 0x05, 0x51, 0x15, 0x03, 0x58, 0},        // 0  - 28 - 031551 05A2FF - 58
  {0x28, 0xFF, 0x2A, 0x06, 0x51, 0x15, 0x03, 0x25, 0},        // 1  - 28 - 031551 062AFF - 25
  {0x28, 0xFF, 0x7A, 0xB3, 0x50, 0x15, 0x02, 0x55, 0},        // 2  - 28 - 021550 B37AFF - 55
  {0x28, 0xFF, 0x6D, 0x38, 0x51, 0x15, 0x03, 0xC0, 0},        // 3  - 28 - 031551 386DFF - C0
  {0x28, 0xFF, 0x57, 0x37, 0x51, 0x15, 0x03, 0x63, 0},        // 4  - 28 - 031551 3757FF - 63
  {0x28, 0xFF, 0x3F, 0xB3, 0x50, 0x15, 0x02, 0x6E, 0}         // 5  - 28 - 021550 B33FFF - 6E
};

float calibration[sizeof(sensorROMRegistry) / 9];
byte sensorID = 0xff;

byte resolution = 9;

void setup(void) {
  Serial.begin(115200);

  for (
    byte _sensorID = 0;
    _sensorID < sizeof(sensorROMRegistry) / 9;
    _sensorID++
  ) {
    calibration[_sensorID] = (float)sensorROMRegistry[_sensorID][8] / 10;
  }
}

void loop(void) {
  byte i;
  byte present = 0;
  byte type_s;

  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;

  //////////////////////////////////////////////////////////////////////////////////////////
  //                                                                                      v
  if ( !ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    resolution++;
    if (resolution > 12) resolution = 9;
    return;                                   // Restart
  }

  Serial.print("ROM =");
  for ( byte i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println(" - CRC is not valid!");
    return;                                   // Restart
  }
  Serial.println();
  //                                                                                      ^
  //////////////////////////////////////////////////////////////////////////////////////////

  sensorID = identifySensor(addr);

  Serial.print("sensorID = ");
  Serial.println(sensorID);


  //////////////////////////////////////////////////////////////////////////////////////////
  //                                                                                      v
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  }
  //                                                                                      ^
  //////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////
  //                                                                                      v
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);         // Read Scratchpad

  //                                                                                      ^
  //////////////////////////////////////////////////////////////////////////////////////////

  Serial.print("  Data = P:");
  Serial.print(present, HEX);
  Serial.print(" D:");

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();

    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  Serial.print("  Resolution=");
  Serial.println(mapResolution(data[4]));

  //////////////////////////////////////////////////////////////////////////////////////////
  //                                                                                      v
  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  //
  int16_t raw = (data[1] << 8) | data[0];

  // DS18S20 or old DS1820
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {

      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);

    // DS18B20
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw &= ~7;  // 9 bit resolution, 93.75 ms

    // DS1820
    else if (cfg == 0x20) raw &= ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw &= ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }

  celsius = (float)raw / 16.0 + (sensorID == 0xff ? 0.0 : calibration[sensorID]);
  fahrenheit = celsius * 1.8 + 32.0;

  //                                                                                      ^
  //////////////////////////////////////////////////////////////////////////////////////////

  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit ");
}

//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      v

byte identifySensor( byte *addr ) {

  for (byte _sensorID = 0; _sensorID < sizeof(sensorROMRegistry) / 9; _sensorID++) {
    byte found = true;
    byte len = 8;
    byte *addr_ = addr;
    while (len-- and found) {
      found = byte(sensorROMRegistry[_sensorID][8 - len - 1]) == byte(*addr_++);
    }
    if (found) return _sensorID;
  }
  return 0xff;
}

//                                                                                      ^
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      v

byte mapResolution(byte data) {
  switch (data)
  {
    case 0x7F:  return 12;
    case 0x5F:  return 11;
    case 0x3F:  return 10;
    case 0x1F:  return 9;
    case 12:    return 0x7F;
    case 11:    return 0x5F;
    case 10:    return 0x3F;
    case 9:     return 0x1F;
    default:    return 0;
  }
}

//                                                                                      ^
//////////////////////////////////////////////////////////////////////////////////////////

bool setResolution(uint8_t newResolution) {

  data[4] = mapResolution(newResolution);
  ds.reset();
  ds.select(addr);
  ds.write(0x4E);
  ds.write(data[2]);
  ds.write(data[3]);
  ds.write(data[4]);
  ds.reset();
  ds.select(addr);
  ds.write(0x48, true); // save the newly written values to eeprom
  delay(20);  // <--- added 20ms delay to allow 10ms long EEPROM write operation (as specified by datasheet)
  delay(10);  // 10ms delay
  ds.reset();
}



