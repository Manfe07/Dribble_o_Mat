#include "bus.h"

#define enablePin   4

byte msg1 = 0;
byte msg2 = 0;

bool status = false;
bool mode = false;
uint8_t msg;
uint16_t value;

double time;

bus bus(enablePin);

void setup() {
  pinMode(13, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6,LOW);
  Serial.begin(115200);
}

void loop() {
  if (time < millis()) {
    time = millis() + 100;
    if (mode) {
      bus.send(on_byte, 0x3456);
      mode = false;
    }
    else {
      bus.send(off_byte, 0xABCD);
      mode = true;
    }
  }
}
void serialEvent() {
  if (bus.get(msg, value)) {
    if (msg == on_byte)
      digitalWrite(13, HIGH);
    if (msg == off_byte)
      digitalWrite(13, LOW);
  }
}

