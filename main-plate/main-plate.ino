#include <RS485_bus.h>
#include <Wire.h>

const int threshold_adr = 5;   //EEPROM-adress of the threshold
const int TalkPin = 4;           //TalkPin of the bus
const int MPU6050_addr = 0x68;

int16_t value;
uint16_t threshold;     //threshold value of the Sensor

unsigned int counter = 0;   //counter for the hits
bool trigger = false;       //bool state if it was allready triggered or not
bool running = false;       //bool state if game is running or not

//create bus
bus bus(TalkPin);

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(115200);

  //get threshold-value from EEPROM
  threshold = ((EEPROM.read(threshold_adr) << 8) | EEPROM.read(threshold_adr + 1));
  //set_threshold(5000);
}//END void setup()


void loop() {
  value = MPU_value();
  if (running) {                              //if running is enabled
    if ((value > (int)threshold) && !trigger) {
      counter ++;
      trigger = true;
      bus.send(C_value, counter);
      //Serial.println("HIGH");
    }
    else if ((value < 0) && trigger) {
      trigger = false;
      //Serial.println("LOW");
    }
  }
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
        //if (ID = bus.get_ID() )      //if msg_ID == my_ID
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

int16_t MPU_value() {
  int16_t buf;
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3F);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr, 2, true);
  buf = Wire.read() << 8 | Wire.read();
  buf -= 15000;
  return buf;
}

