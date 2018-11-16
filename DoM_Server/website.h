// ========================================================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "./javascript.h"

unsigned long wait000 = 0UL, wait001 = 1000UL;
uint16_t counter_1 = 1;
uint16_t counter_2 = 2;
uint16_t sensetiv = 400;
uint16_t duration = 30;
double rtime = 0;


String  mainPage_start, mainPage_end, Page_1, Page_2, setPage, XML, modeText;

ESP8266WebServer server(80);

void buildMain() {
  buildJavascript();
  mainPage_start = "<!DOCTYPE HTML>\n";
  mainPage_start += "<META name='viewport' content='width=device-width, initial-scale=1'>\n";
  mainPage_start += "<head><style type='text/css'>\n";
  mainPage_start += "#middlediv{vertical-align:middle;}\n";
  mainPage_start += "</style>";
  mainPage_start += "</head>\n";
  mainPage_start += javaScript;
  mainPage_start += "<BODY style='text-align:center; font-size:10vmin; line-height: 0.7;font-family:Arial, bold; background-color:#ffc560; ' onload='process()'>\n";
  mainPage_start += "<div id='middlediv'>\n";
  mainPage_end += "</div>\n";
  mainPage_end += "</BODY>\n";
  mainPage_end += "</HTML>\n";
}

void buildPage_1() {
  Page_1 += mainPage_start;
  Page_1 += "<h2><p id='p1'><A ID='gameMode'></A></p>\n";
  Page_1 += "<p id='p1'><A ID='runtime'></A></p>\n";
  Page_1 += "<p id='p1'><A ID='hits_1'></A></p></h2>\n";
  Page_1 += mainPage_end;
}

void buildPage_2() {
  Page_2 += mainPage_start;
  Page_2 += "<h2><p id='p1'><A ID='gameMode'></A></p>\n";
  Page_2 += "<p id='p1'><A ID='runtime'></A></p>\n";
  Page_2 += "<p id='p1'><A ID='hits_2'></A></p></h2>\n";
  Page_2 += mainPage_end;
}

void buildSet() {
  buildJavascript();
  setPage = "<!DOCTYPE HTML>\n";
  setPage += "<META name='viewport' content='width=device-width, initial-scale=1'>\n";
  setPage += javaScript;
  setPage += "<BODY style='text-align:center' onload='process()'>\n";
  setPage += "<h1>Dribble O Mat</h1><BR><h2>Settings</h2><BR><BR>\n";
  setPage += "Duration (sec): <input type='number' id='duration' style='width:50px;' value = " + (String)duration + ">\n";
  setPage += "<button onclick='duration_set()',>Set</button><BR>\n";
  setPage += "Sensetivity: <input type='number' id='sensetiv' style='width:50px;' value = " + (String)sensetiv + ">\n";
  setPage += "<button onclick='sensetiv_set()',>Set</button><BR>\n";
  setPage += "</BODY>\n";
  setPage += "</HTML>\n";
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
  XML += modeText;
  XML += "</mode>";
  XML += "<durationVal>";
  XML += duration;
  XML += "</durationVal>";
  XML += "<sensetivVal>";
  XML += sensetiv;
  XML += "</sensetivVal>";
  XML += "<counter_1>";
  XML += (String)counter_1;
  XML += "</counter_1>";
  XML += "<counter_2>";
  XML += (String)counter_2;
  XML += "</counter_2>";
  XML += "</xml>";
}

void handlePage_1() {
  buildMain();
  buildPage_1();
  server.send(200, "text/html", Page_1);
}

void handlePage_2() {
  buildMain();
  buildPage_2();
  server.send(200, "text/html", Page_2);
}

void handleSet() {
  buildSet();
  server.send(200, "text/html", setPage);
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
