#include "EEPROM.h"

#define threshold_adr   2   //EEPROM-adress of the threshold
#define time_out      200   //timeout for RS485

#define TalkPin 5

unsigned int threshold;


void setup() {
  threshold = ((EEPROM.read(threshold_adr) << 8) & EEPROM.read(threshold_adr + 1));
}

void loop() {
}

void serialEvent() {

}

void send_data(byte code, unsigned int value)
{
  float time_end = millis() + time_out;
  pinMode(TalkPin, INPUT);
  while (digitalRead(TalkPin)) {
    if (time_end <= millis())
      break;
  }
  pinMode(TalkPin, OUTPUT);
  digitalWrite(TalkPin, HIGH);
  Serial.write(code);
  Serial.write(value);
  digitalWrite(TalkPin, LOW);
}
