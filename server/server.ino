/*
 * Sketch for ESP8266.
 * Tested on WeMos D1(R1).
 * 
 * @author MaxVerevkin
 */

#include <ESP8266WiFi.h>

//WiFi credits
#define _SSID "**********"
#define _PASS "**********"

//Serial baud rate (comment #define to disable Serial) (LED_BUILTIN cant be uset at the same time as Serial)
#define _SERIAL_BR 9600

//Main page content
#define main_page "\
<!DOCTYPE html>\
<html>\
  <head>\
    <meta charset=\"ASCII\"/>\
    <title>Remote Controll</title>\
    <style>\
      .btn {\
        width:200px;\
        height:200px;\
      }\
    </style>\
  </head>\
  <body>\
    <div style=\"text-align:center;\">\
      <button class=\"btn\" style=\"background:url(https://maxverevkin.github.io/au.png)\" type=\"button\" id=\"au\"/>\
    </div>\
    <div style=\"text-align:center;\">\
      <button class=\"btn\" style=\"background:url(https://maxverevkin.github.io/al.png)\" type=\"button\" id=\"al\"/>\
      <button class=\"btn\" style=\"background:url(https://maxverevkin.github.io/ci.png)\" type=\"button\" id=\"ci\"/>\
      <button class=\"btn\" style=\"background:url(https://maxverevkin.github.io/ar.png)\" type=\"button\" id=\"ar\"/>\
    </div>\
    <div style=\"text-align:center;\">\
      <button class=\"btn\" style=\"background:url(https://maxverevkin.github.io/ad.png)\" type=\"button\" id=\"ad\"/>\
    </div>\
    <script>\
      function setEvents(item) {\
        var img = document.getElementById(item);\
        img.addEventListener(\"touchstart\", event => {\
          sendRequest('d' + item);\
        });\
        img.addEventListener(\"touchend\", event => {\
          sendRequest('u' + item);\
        });\
      }\
      function sendRequest(req) {\
        var xhttp = new XMLHttpRequest();\
        xhttp.open(\"GET\", req, true);\
        xhttp.send();\
      }\
      \
      setEvents(\"au\");\
      setEvents(\"al\");\
      setEvents(\"ci\");\
      setEvents(\"ar\");\
      setEvents(\"ad\");\
    </script>\
  </body>\
</html>"

//Web server on potr 80
WiFiServer server(80);

void setup() {
  //Initialize Serial
  #ifdef _SERIAL_BR
    Serial.begin(_SERIAL_BR);
    while (!Serial) {
      delay (20);
    }
    Serial.println();
    Serial.print("Connecting to SSID: ");
    Serial.print(_SSID);
    Serial.print("...");
  #endif
  
  //Connect to WiFi
  WiFi.begin(_SSID, _PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  #ifdef _SERIAL_BR
    Serial.println(" [ DONE ]");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Starting server...");
  #endif

  //Start web server
  server.begin();

  #ifdef _SERIAL_BR
    Serial.println(" [ DONE ]");
  #endif
}

void loop() {
  #ifdef _SERIAL_BR
    Serial.println();
    Serial.println("Waiting for client");
  #endif
  
  //Wait for client
  WiFiClient client;
  while (!(client = server.available()));

  #ifdef _SERIAL_BR
    Serial.println("New client");
  #endif

  //Wait for client's data
  while (!client.available());

  //Parse request
  byte state = 0;
  String meth = "";
  String file = "";
  String http = "";

  while (client.available()) {
    char c = client.read();
    if (c == ' ') {
      state += 1;
      continue;
    } if (c == '\n') {
      break;
    }
    switch (state) {
      case 0:
        meth += c;
        break;
      case 1:
        file += c;
        break;
      default:
        http += c;
        break;
    }
  }
  client.flush();

  #ifdef _SERIAL_BR
    Serial.println("Request: ");
    Serial.print(  "Method:  ");
    Serial.println(          meth);
    Serial.print(  "File:    ");
    Serial.println(          file);
    Serial.print(  "Http:    ");
    Serial.println(          http);
  #endif

  //If method is not GET, return
  if (meth != "GET") {
    #ifdef _SERIAL_BR
      Serial.println("Client disconected");
    #endif
    return;
  }
  
  if (file == "/") {
    client.print(main_page);
    #ifdef _SERIAL_BR
      Serial.println("Client disconected");
    #endif
    return;
  } if (file.length() != 4) {
    #ifdef _SERIAL_BR
      Serial.println("Client disconected");
    #endif
    return;
  }

  //8 varinats of input
  
  //Pushed:
  if (file.equals("/dau")) { //Up
    
  } else if (file.equals("/dal")) { //Left
    
  } else if (file.equals("/dci")) { //Center
    
  } else if (file.equals("/dar")) { //Left
    
  } else if (file.equals("/dad")) { //Left
    
  }

  //Relised:
  if (file.equals("/uau")) { //Up
    
  } else if (file.equals("/ual")) { //Left
    
  } else if (file.equals("/uci")) { //Center
    
  } else if (file.equals("/uar")) { //Left
    
  } else if (file.equals("/uad")) { //Left
    
  }
  

  #ifdef _SERIAL_BR
    Serial.println("Client disconected");
  #endif
}
