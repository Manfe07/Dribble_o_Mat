#include "DoM_Server.h"

uint16_t get_duration() {
  uint16_t value = (EEPROM.read(dr_adr) << 8) | (EEPROM.read(dr_adr + 1));
  return value;
}

void save_duration(uint16_t _value) {
  uint8_t part1, part2;
  part1 = (_value & 0xFF00) >> 8;
  part2 = (_value & 0x00FF);
  EEPROM.write(dr_adr, part1);
  EEPROM.write(dr_adr + 1, part2);
}
