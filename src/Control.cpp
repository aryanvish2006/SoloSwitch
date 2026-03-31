#include<Arduino.h>
#include"Control.h"

Control control;

void Control::begin(){
    pinMode(relay,OUTPUT);
    pinMode(led,OUTPUT);
}

void Control::on(){
    digitalWrite(relay,HIGH);
    digitalWrite(led,HIGH);
}
void Control::off(){
    digitalWrite(relay,LOW);
    digitalWrite(led,LOW);
}
