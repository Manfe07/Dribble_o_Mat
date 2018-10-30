#include "DoM.h"

void device::send(unsigned char trg,  unsigned char code, unsigned int value)
{
  Wire.begin();
  Wire.beginTransmission(trg);
  Wire.write(code);
  Wire.write(value);
  Wire.endTransmission();
}

bool device::data_available()
{
  Wire.begin(device::ID);
  if(Wire.available() >= 3)
    return true;
  else
    return false;
}

