#include "DoM.h"

#define threshold_adr   2   //EEPROM-adress of the threshold

unsigned int threshold;

device bus;

void setup() {
  bus.ID = 0x01;
  threshold = threshold_get();
}

void loop() {
  if (bus.data_available()) {
    byte Code = Wire.read();
    unsigned int Value = Wire.read();
  }
}

unsigned int threshold_get()
{
  return ((EEPROM.read(threshold_adr) << 8) & (EEPROM.read(threshold_adr + 1)));
}


