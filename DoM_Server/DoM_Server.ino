#include "DoM_Server.h"

#define enablePin   4

uint16_t duration;
uint8_t status;
double target_time;

bus bus(enablePin);

void setup() {
  duration = get_duration();
  Serial.begin(115200);
}

void loop() {
  if (target_time <= millis() && status == M_ready) {
    target_time += 1000;
    status = M_set;
    bus.send(C_gameM, M_set);
    digitalWrite(13, LOW);
  }
  else if (target_time <= millis() && status == M_set) {
    target_time += (duration * 1000);
    status = M_start;
    bus.send(C_gameM, M_start);
    digitalWrite(13, HIGH);
  }
  else if (target_time <= millis() && status == M_start) {
    status = M_stop;
    bus.send(C_gameM, M_stop);
    digitalWrite(13, LOW);
  }
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
        break;
      case C_setTime:
        duration = value;
        save_duration(duration);
        bus.send(code, value);
        break;
      default:
        break;
    }
  }
}

void gameMode(uint16_t _mode) {
  if (_mode == M_tstart) {
    status = M_ready;
    target_time = millis() + 1000;
    digitalWrite(13, HIGH);
    bus.send(C_gameM, M_ready);
  }
}
