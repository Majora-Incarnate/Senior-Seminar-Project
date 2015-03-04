#ifndef CLOCK_H
#define CLOCK_H



#include "System.h"



class Clock {
public:
    static Clock Frame_Control;
    
    Clock();
    void Update();

    int Get_FPS();
    double Get_TPF();

private:
    int old_time;
    int last_time;

    double speed_factor;
    double delta;

    int num_of_frames;
    int frames;
};



#endif
