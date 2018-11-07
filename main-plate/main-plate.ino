#include "bus.h"

#define threshold_adr   5   //EEPROM-adress of the threshold
#define TalkPin 4           //TalkPin of the bus

unsigned int threshold;     //threshold value of the Sensor
unsigned int counter = 0;   //counter for the hits
bool trigger = false;       //bool state if it was allready triggered or not
bool running = false;       //bool state if game is running or not

//create bus
bus bus(TalkPin);

void setup() {

  Serial.begin(115200);

  //get threshold-value from EEPROM
  threshold = ((EEPROM.read(threshold_adr) << 8) | EEPROM.read(threshold_adr + 1));
}//END void setup()


void loop() {
  /*
  if (running) {                              //if running is enabled
    if (digitalRead(5) && !trigger) {
      counter ++;
      trigger = true;
      bus.send_data(C_value, counter);
    }
    else if (!digitalRead(5) && trigger) {
      trigger = false;
    }
  }
  */
  bus.send(C_value, 1);
  delay(250);
  bus.send(C_value, 0);
  delay(250);
}//END void loop()


void serialEvent() {
  //function variables
  uint8_t ID, code;
  uint16_t value;

  if (bus.get(ID, code, value)) {  //get data from the bus

    switch (code) {
      case C_gameM:
        set_GameMode(value);
        break;

      case C_setID:
        bus.set_ID(ID);   //set device ID
        break;

      case C_setTH:
        if (ID = bus.get_ID() )      //if msg_ID == my_ID
          set_threshold(value);   //set the threshold of the sensor
        break;

      default:
        break;
    }
  }
}//END void SerialEvent()


void set_GameMode(uint16_t _value) {
  switch (_value) {
    case M_start:
      running = true;
      break;

    case M_stop:
      running = false;
      counter = 0;
      break;

    default:
      break;
  }
}//END void set_GameMode(...)



void set_threshold(unsigned int value) {
  threshold = value;
  byte th1 = ((value & 0xFF00) >> 8);              //splitt the threshold into two bytes
  byte th2 = (value & 0x00FF);
  EEPROM.write(threshold_adr, th1);     //store the bytes in EEPROM
  EEPROM.write(threshold_adr + 1, th2);
}//END void set_threshold(...)
