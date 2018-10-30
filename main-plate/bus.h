#ifndef BUS_H
#define BUS_H

#include "arduino.h"

#define time_out      200   //timeout for RS485

class bus{
  private:
        int TalkPin;
  public:
        bus(int);
        void send_data(byte, unsigned int);
        void get_data(byte&, unsigned int&);
};

#endif
