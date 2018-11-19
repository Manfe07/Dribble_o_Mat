#include "DoM_Server.h"
#include "website.h"
#include <WiFiManager.h>

//#define DEBUG

const int enablePin = D2;
const int wifiPin = D5;

uint8_t status;
double target_time;
uint16_t old_sensetiv;
uint16_t old_duration;

WiFiManager wifiManager;
bus bus(enablePin);

void setup() {
  //duration = get_duration();
  Serial.begin(115200);
  pinMode(wifiPin, INPUT);
  pinMode(LED_BUILTIN , OUTPUT);
#ifndef DEBUG
  wifiManager.setDebugOutput(false);
#endif
  if (digitalRead(wifiPin)) {
    digitalWrite(LED_BUILTIN, LOW);
    wifiManager.autoConnect("DoM-Wifi");
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH);
    wifiManager.startConfigPortal("DoM-Wifi-Setup");
  }

  Serial.println(WiFi.SSID());
  Serial.println(WiFi.localIP());

  server.on("/",          handlePage_1);
  server.on("/1",         handlePage_1);
  server.on("/2",         handlePage_2);
  server.on("/set",       handleSet);
  server.on("/xml",       handleXML);
  server.on("/setESPval", handleESPval);
  server.begin();

  modeText = "Hallo";

}

void loop() {
  server.handleClient();
  serialEvent();
  //------------------------------------------------------------------------------------------------------------------------


  if (target_time <= millis() && status == M_ready) {
    target_time += 1000;
    status = M_set;
    modeText = "SET";
    bus.send(C_gameM, M_set);
    digitalWrite(13, LOW);
  }
  else if (target_time <= millis() && status == M_set) {
    target_time += (duration * 1000);
    status = M_start;
    modeText = "GO!";
    bus.send(C_gameM, M_start);
    digitalWrite(13, HIGH);
  }
  else if (target_time <= millis() && status == M_start) {
    status = M_stop;
    modeText = "FINISH";
    bus.send(C_gameM, M_stop);
    digitalWrite(13, LOW);
  }

  if (status == M_start) {
    rtime = target_time - millis();
  }
  if (sensetiv != old_sensetiv) {
    if (bus.send(C_setTH, sensetiv))
      old_sensetiv = sensetiv;
  }
  if (duration != old_duration) {
    if (bus.send(C_setTime, duration)) {
      old_duration = duration;
      save_duration(duration);
    }
  }
}


void serialEvent() {
  uint8_t ID, code;
  uint16_t value;

  if (bus.get(ID, code, value)) {
    switch (code) {
      case C_setID:
        bus.set_ID(ID);
        bus.send(code, value);
        break;
      case C_gameM:
        gameMode(value);
        break;
      case C_setTime:
        duration = value;
        save_duration(duration);
        bus.send(code, value);
        break;
      case C_value:
        if (status == M_start) {
          if (ID == 0x01)
            counter_1 = value;
          if (ID == 0x02)
            counter_2 = value;
        }
        break;
      default:
        break;
    }
  }
}

void gameMode(uint16_t _mode) {
  if (_mode == M_tstart) {
    status = M_ready;
    modeText = "READY";
    counter_1 = 0;
    target_time = millis() + 1000;
    digitalWrite(13, HIGH);
    bus.send(C_gameM, M_ready);
  }
}
