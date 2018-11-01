#include "bus.h"

bus::bus(int TP)
{
  TalkPin = TP;
}//END bus::bus(...)

void bus::send_data(byte code, unsigned int value)
{
  code &= B00001111;              //make sure that code only uses last 4Bit
  code |= ID;                     //integrade ID(0000AAAA) into code(0000CCCC) => code = AAAACCCC

  float time_end = millis() + time_out;   //Define time for timeout

  pinMode(TalkPin, INPUT);        //set TalkPin as Input, to listen if someone talks on the Bus
  while (digitalRead(TalkPin)) {  //Wait till bus is free
    if (time_end <= millis())     //Break if timeout
      break;
  }
  pinMode(TalkPin, OUTPUT);       //set TalkPin as Output
  digitalWrite(TalkPin, HIGH);    //set TalkPin high to use Bus
  Serial.write(start_byte);       //First send start-Byte
  Serial.write(code);             //send ID and Code combination
  Serial.write(value);            //send 2 byte of data/value
  Serial.write(stop_byte);        //send stop_byte for validation
  digitalWrite(TalkPin, LOW);     //set TalkPin low to set the bus free
  pinMode(TalkPin, INPUT);        //set TalkPin as Input, to listen if someone talks on the Bus
}//END void bus::send_data(...)


int bus::get_data(byte& ID, byte& code, unsigned int& value)
{
  byte data[5];
  if (Serial.available() >= 5)
  {
    for (int i = 0; i < 5; i++) {
      data[i] = Serial.read();
    }
    if ((data[0] == start_byte) && (data[4] == stop_byte))
    {
      code = (data[1] & B00001111);
      ID = ((data[1] & B11110000)  >> 4);
      value = ((data[2] << 8) & data[3]);
      return 1;   //if data is "valid" return 1
    }
    else
      return -1;  //if data is not valid, return -1
  }
  else {
    return -6;   //if not enought bytes available, return -6
  }
}//END void bus::get_data(...)


void bus::set_ID(byte id) {
  ID = (id << 4);
}//END void bus::set_ID(...)
