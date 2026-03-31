#include<Arduino.h>
#include<IRremoteESP8266.h>
#include<IRrecv.h>
#include<IRutils.h>
#include"TimerManager.h"
#include"Control.h"
#include"Web.h"

#define IR_PIN D6

IRrecv irrecv(IR_PIN);
decode_results results;

bool state = false;

void setup(){
  control.begin();
  web.begin();

  irrecv.enableIRIn();
}
void loop(){
  if(irrecv.decode(&results)){

    unsigned long code = results.value;

    if( code != 0xFFFFFFFF){
      if(code == 0x1FE48B7){
        state = !state;
        state?control.on():control.off();
      }else if( code == 0x1FE58A7){
        timer.startTimer(3000,false);
      }
    }
    irrecv.resume();
  }
  timer.loop();
  web.loop();
}