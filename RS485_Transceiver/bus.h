#ifndef BUS_H
#define BUS_H

#include "arduino.h"

#define start_byte  B11110101
#define stop_byte   B00001101

#define on_byte     B01101001
#define off_byte    B01101111

class bus {
  private:
    int enablePin;
  public:
    bus(int);
    int get(uint8_t&, uint16_t&);
    int send(uint8_t, uint16_t);
};
#endif
