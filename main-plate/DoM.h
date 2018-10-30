#ifndef dom_h
#define dom_h

#define C_ASK_ID    B0000000
#define C_SEND_ID   B0000001

#include <Wire.h>
#include <EEPROM.h>

class device{
  private:
  
  public:
      int ID;
      void send(unsigned char,unsigned char,unsigned int);
      bool data_available();
};

#endif
