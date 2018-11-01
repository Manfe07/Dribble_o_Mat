#include "bus.h"

bus::bus(int TP)
{
  TalkPin = TP;
  Serial.begin(9600);
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
  Serial.write(code);             //first write ID and Code combination
  Serial.write(value);            //second send 2 byte of data/value
  digitalWrite(TalkPin, LOW);     //set TalkPin low to set the bus free
  pinMode(TalkPin, INPUT);        //set TalkPin as Input, to listen if someone talks on the Bus
}//END void bus::send_data(...)


int bus::get_data(byte& ID, byte& code, unsigned int& value)
{
  byte data[3];
  if (Serial.available() >= 3)
  {
    for (int i = 0; i < 3; i++) {
      data[i] = Serial.read();
    }
    code = (data[0] & B00001111);
    ID = ((data[0] & B11110000)  >> 4);
    value = ((data[2] << 8) & data[1]);
    
    return 1;   //if data is "valid" return 1
  }
  else {
    return 0;   //if data is not "valid" return 0
  }
}//END void bus::get_data(...)


void bus::set_ID(byte id) {
  ID = (id << 4);
}//END void bus::set_ID(...)

