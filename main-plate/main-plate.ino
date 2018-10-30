#include "bus.h"
#include "EEPROM.h"


#define threshold_adr   5   //EEPROM-adress of the threshold
#define C_Counter B00000010

#define TalkPin 2

unsigned int threshold;
bool trigger = false;
unsigned int counter = 0;

bus bus(TalkPin);

void setup() {
  threshold = ((EEPROM.read(threshold_adr) << 8) & EEPROM.read(threshold_adr + 1));
}


void loop() {
  if (digitalRead(5) && !trigger)
  {
    counter ++;
    trigger = true;
    bus.send_data(C_Counter, counter);
  }
}

void serialEvent() {
  byte code;
  unsigned int value;
  bus.get_data(code, value);

  switch (code) {
    case B0000001:
      break;
  }
}
