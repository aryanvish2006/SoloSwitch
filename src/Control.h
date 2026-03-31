#pragma once

#define relay D1
#define led D2

class Control {
    public:
    void begin();
    void on();
    void off();
};

extern Control control;