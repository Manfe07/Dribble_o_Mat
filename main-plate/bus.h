#ifndef BUS_H
#define BUS_H

#include "EEPROM.h"
#include "arduino.h"

//Bus Message code
#define C_Stop      B00000000   //Stop - Stop measuring
#define C_Start     B00000001   //Start - measuring
#define C_Countdwn  B00000010   //Start - Countdown
#define C_setID     B00000011   //*Set Device-ID of all connected Devices *more information below*
#define C_Value     B00000100   //Counter-Value 
#define C_setTH     B00000101   //set the threshold of the sensor
#define C_setTime   B00000111   //set the time for a round

/*  ---INFO---
 *  if you want to set the device ID, you should ONLY connect the device you want to set the ID
 */

#define time_out      200   //timeout for RS485

class bus{
  private:
        int TalkPin;
        byte ID = 0;
  public:
        bus(int);
        void send_data(byte, unsigned int);
        int get_data(byte&, byte&, unsigned int&);
        void set_ID(byte);
};

#endif
