#include "bus.h"

bus::bus(int TP)
{
  TalkPin = TP;
  pinMode(TalkPin, OUTPUT);
}//END bus::bus(...)

int bus::send_data(byte code, unsigned int value)
{
  if (Serial.available() == 0) {  //check if data is available, befor sending data on the bus
    code &= 0x0F;              //make sure that code only uses last 4Bit
    code |= ID;                     //integrade ID(0000AAAA) into code(0000CCCC) => code = AAAACCCC

    float time_end = millis() + time_out;   //Define time for timeout

    byte data[8] = {start_byte, code, 0xFF ^ code, 0, 0, 0 , 0 , stop_byte};
    data[3] = (value & 0xFF00) >> 8;
    data[5] = (value & 0x00FF);
    data[4] = 0xFF ^ data[3];
    data[6] = 0xFF ^ data[5];

    digitalWrite(TalkPin, HIGH);    //set TalkPin high to use Bus
    for (int i = 0; i < 8; i++)
      Serial.write(data[i]);        //send data package
    digitalWrite(TalkPin, LOW);     //set TalkPin low to set the bus free

    return 1;                       //return 1 after data was sended
  }//END if(Serial.available == 0)
  else {
    return -1;  //if data is on the bus, return -1
  }
}//END void bus::send_data(...)


int bus::get_data(byte& ID, byte& code, unsigned int& value)
{
  byte data[8];

  if (Serial.available() > 0)
  {
    //(0) = start_byte; (1) = msg_code; (2) = !msg_code; (3) = value 1/2; (4) = !value 1/2; (5) = value 2/2; (6) = !value 2/2; (7) = stop_byte;

    data[0] = Serial.read();          //get first byte

    if (data[0] == start_byte) {      //if first byte == start_byte ...
      for (int i = 1; i < 8; i++) {   //get other 7 byte
        data[i] = Serial.read();
      }
      if ((data[0] == start_byte) && (data[7] == stop_byte)) {                        //check if message has start_byte and stop_byte
        if ((data[1] ^ data[2]) && (data[3] ^ data[4]) && (data[5] ^ data[6])) {      //check if received data is valid
          code = (data[1] & 0x0F);                                                    //msg code are the last 4 bit of the 2. byte from msg
          ID = ((data[1] & 0xF0)  >> 4);                                              //ID are the first 4 bit of the 2. byte from msg
          value = ((data[3] << 8) & data[5]);                                         //the value part are the 3. and 5. byte
          return 1;   //if data is "valid" return 1
        }//END if("data valid")
        else
          return -2;                                                                  //if message is not valid, return -2
      }//END if("data is complete")
      else
        return -3;                                                                    //if message has no start_byte and stop_byte, return -3
    }//END if("first byte == start_byte")
    else
      return -1;  //if data is not valid, return -1                                   //if the first received byte is not the start_byte, return -1
  }//END if(Serial.available() > 0);
  else
    return 0;   //if not enought bytes available, return -6                           //if no byte available, return 0
}//END void bus::get_data(...)


void bus::set_ID(byte id) {
  ID = (id << 4);
}//END void bus::set_ID(...)
