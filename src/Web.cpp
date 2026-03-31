#include<Arduino.h>
#include"Web.h"
#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<LittleFS.h>
#include<TimerManager.h>
#include"Control.h"

Web web;

ESP8266WebServer server(80);

const char* ssid = "ARYAN_RELAY";
const char* pass = "12345678";

void Web::begin(){
    if(!LittleFS.begin()) return;

    WiFi.softAP(ssid,pass);

    server.on("/",[](){
        File file = LittleFS.open("index.html","r");
        server.streamFile(file,"text/html");
        file.close();
    });

    server.on("/on",[](){
        control.on();
    });
    server.on("/off",[](){
        control.off();
    });

    server.on("/timer",[](){
        if(!server.hasArg("time") || !server.hasArg("state")) return;

        int time = server.arg("time").toInt();
        int state = server.arg("state").toInt();
        timer.startTimer(time*1000,state);
    });

    server.on("/getRemainingSec",[](){
        int sec = timer.remainingSec();
        bool state = timer.getTargetState();

        server.send(200,"text/plain",String(sec)+state?"_ON":"_OFF");
    });

    server.begin();
}

void Web::loop(){
    server.handleClient();
}
