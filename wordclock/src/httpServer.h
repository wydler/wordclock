#ifndef WORDCLOCK_SERVER_H
#define WORDCLOCK_SERVER_H

#include <AutoConnect.h>
#include <ESP8266WebServer.h>

class HttpServer {
  public:
    static ESP8266WebServer web;
    static AutoConnect portal;
    static AutoConnectConfig config;
    static String ip;
    
    static void setup();
    static void loop();
};

#endif
