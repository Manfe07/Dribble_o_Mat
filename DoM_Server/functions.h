// ========================================================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "./javascript.h"

unsigned long wait000 = 0UL, wait001 = 1000UL;
uint16_t counter = 0;
uint16_t sensetiv = 400;
uint16_t duration = 30;
double rtime = 0;


ESP8266WebServer server(80);

void buildMain() {
  buildJavascript();
  mainPaige = "<!DOCTYPE HTML>\n";
  mainPaige += "<META name='viewport' content='width=device-width, initial-scale=1'>\n";
  mainPaige += "<head><style type='text/css'>\n";
  mainPaige += "#middlediv{vertical-align:middle;}\n";
  mainPaige += "</style>";
  mainPaige += "</head>\n";
  mainPaige += javaScript;
  mainPaige += "<BODY style='text-align:center; font-size:10vmin; line-height: 0.7;font-family:Arial, bold; background-color:#ffc560; ' onload='process()'>\n";
  mainPaige += "<div id='middlediv'>\n";
  mainPaige += "<h2><p id='p1'><A ID='gameMode'></A></p>\n";
  mainPaige += "<p id='p1'><A ID='runtime'></A></p>\n";
  mainPaige += "<p id='p1'><A ID='hits'></A></p></h2>\n";
  mainPaige += "</div>\n";
  mainPaige += "</BODY>\n";
  mainPaige += "</HTML>\n";
}

void buildSet() {
  buildJavascript();
  setPaige = "<!DOCTYPE HTML>\n";
  setPaige += "<META name='viewport' content='width=device-width, initial-scale=1'>\n";
  setPaige += javaScript;
  setPaige += "<BODY style='text-align:center' onload='process()'>\n";
  setPaige += "<h1>Dribble O Mat</h1><BR><h2>Settings</h2><BR><BR>\n";
  setPaige += "Duration (sec): <input type='number' id='duration' style='width:50px;' value = " + (String)duration + ">\n";
  setPaige += "<button onclick='duration_set()',>Set</button><BR>\n";
  setPaige += "Sensetivity: <input type='number' id='sensetiv' style='width:50px;' value = " + (String)sensetiv + ">\n";
  setPaige += "<button onclick='sensetiv_set()',>Set</button><BR>\n";
  setPaige += "</BODY>\n";
  setPaige += "</HTML>\n";
}

String millis2time() {
  String Time = "";
  double ss;
  byte mm;
  ss = rtime;
  ss = ss / 1000;
  mm = ss / 60;
  ss = ss - mm * 60;
  if (mm < 10)Time += "0";
  Time += (String)mm + ":";
  if (ss < 10)Time += "0";
  Time += (String)ss;
  return Time;
}

void buildXML() {
  XML = "<?xml version='1.0'?>";
  XML += "<xml>";
  XML += "<millistime>";
  XML += millis2time();
  XML += "</millistime>";
  XML += "<mode>";
  XML += mode_w;
  XML += "</mode>";
  XML += "<durationVal>";
  XML += duration;
  XML += "</durationVal>";
  XML += "<sensetivVal>";
  XML += sensetiv;
  XML += "</sensetivVal>";
  XML += "<counter>";
  XML += (String)counter;
  XML += "</counter>";
  for (int i = 0; i < sliderMAX; i++) {
    XML += "<sliderval" + (String)i + ">";
    XML += String(sliderVal[i]);
    XML += "</sliderval" + (String)i + ">";
    XML += "<ESPval" + (String)i + ">";
    ESPval[i] = 9 * (100 - sliderVal[i]) + 100;
    XML += String(ESPval[i]);
    XML += "</ESPval" + (String)i + ">";
  }
  XML += "</xml>";
}

void handleMain() {
  buildMain();
  server.send(200, "text/html", mainPaige);
}

void handleSet() {
  buildSet();
  server.send(200, "text/html", setPaige);
}

void handleXML() {
  buildXML();
  server.send(200, "text/xml", XML);
}

void handleESPval() {
  if (server.arg("var") == "duration") {
    duration =  server.arg("val").toInt();
    if (duration < 5) duration = 5;
  }
  else if (server.arg("var") == "sensetiv") {
    sensetiv = server.arg("val").toInt();
  }
  buildXML();
  server.send(200, "text/xml", XML);
}
