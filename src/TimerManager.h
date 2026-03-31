#pragma once

class Timer{
    public:
    void startTimer(unsigned long timeMs , bool state);
    void loop();
    void cancelTimer();
    int remainingSec();
    bool getTargetState();

    private:
    void activate();
};

extern Timer timer;