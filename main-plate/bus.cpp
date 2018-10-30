#include "bus.h"

bus::bus(int TP)
{
  TalkPin = TP;
  Serial.begin(9600);
}

void bus::send_data(byte code, unsigned int value)
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

void bus::get_data(byte& code, unsigned int& value)
{
  byte data[3];
  if (Serial.available() >= 3)
  {
    for (int i = 0; i < 3; i++) {
      data[i] = Serial.read();
    }
    code = data[0];
    value = ((data[2] << 8) & data[1]);
  }
}

