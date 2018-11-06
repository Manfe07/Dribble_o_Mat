#include "bus.h"

bus::bus(int Pin) {
  enablePin = Pin;
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
}

int bus::get(byte& code, unsigned int& value) {
#define msg_l   5
  if (Serial.available() >= msg_l) {
    uint8_t data[msg_l];
    data[0] = Serial.read();
    if (data[0] == start_byte) {
      for (int i = 1; i < msg_l; i++) {
        data[i] = Serial.read();
      }
      if (data[msg_l - 1] == stop_byte) {
        code = data[1];
        value = (data[2] << 8) & data[3];
        return 1;
      }
      else
        return 0;
    }
    else
      return 0;
  }
  else
    return 0;
}

int bus::send(byte data1, unsigned int value) {
  byte data2 = ((value & 0xFF00) >> 8);
  byte data3 = (value & 0x00FF);
  if (Serial.available() == 0) {
    digitalWrite(enablePin, HIGH);
    Serial.write(start_byte);
    Serial.write(data1);
    Serial.write(data2);
    Serial.write(data3);
    Serial.write(stop_byte);
    delay(1);
    digitalWrite(enablePin, LOW);
    return 1;
  }
  else
    return 0;
}

