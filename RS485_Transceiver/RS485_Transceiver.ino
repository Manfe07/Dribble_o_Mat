#include "bus.h"

#define enablePin   4

bool status = false;

double time;

bus bus(enablePin);

void setup() {
  pinMode(13, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  Serial.begin(115200);
}

void loop() {
  /*
    if (time < millis()) {
    time = millis() + 100;
    if (status) {
      bus.send(M_start, M_start);
      status = false;
    }
    else {
      bus.send(M_stop, M_stop);
      status = true;
    }
    }
  */
}

void serialEvent() {
  uint8_t ID, code;
  uint16_t value;

  if (bus.get(ID, code, value)) {
    switch (code) {
      case C_setID:
        bus.set_ID(ID);
        bus.send(code, value);
        break;
      case C_gameM:
        gameMode(value);
        bus.send(code, value);
        break;
      default:
        break;
    }
  }
}

void gameMode(uint16_t _mode) {
  if (_mode == M_start)
    digitalWrite(13, HIGH);
  else if (_mode == M_stop)
    digitalWrite(13, LOW);
}

