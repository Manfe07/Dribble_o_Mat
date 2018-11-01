#ifndef BUS_H
#define BUS_H

#include "EEPROM.h"
#include "arduino.h"


//Start- and Stop-Byte for message validation
#define start_byte  B10011101
#define stop_byte   B11011101

//Bus Message code
#define C_gameM     B00000000   //Game-Mode (Ready, Set, Start, Stop,)
#define C_setID     B00000001   //*Set Device-ID of all connected Devices *more information below*
#define C_value     B00000010   //Counter-Value 
#define C_setTH     B00000011   //set the threshold of the sensor
#define C_setTime   B00000100   //set the time for a round

//Game Mode code
#define M_ready     B00000010
#define M_set       B00000011
#define M_start     B00000001
#define M_stop      B00000000


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
