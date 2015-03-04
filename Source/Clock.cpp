#include "Clock.h"



Clock Clock::Frame_Control;



Clock::Clock() {
    old_time = 0;
    last_time = 0;

    speed_factor = 0.0;

    frames = 0;
    num_of_frames = 0;
}

void Clock::Update() {
    int temp = SDL_GetTicks();
    
    if(old_time + 1000 < temp) {
        old_time = temp;
        
        num_of_frames = frames;
        frames = 0;
    }

    delta = 1.0 / System::fps_limit;
    speed_factor = (temp - last_time) / 1000.0;
    last_time = temp;
    frames++;
    
    int delay = (delta - speed_factor) * 1000;
    if (delay > 0)
        SDL_Delay(delay);
        
}

int Clock::Get_FPS() {
    return num_of_frames;
}

double Clock::Get_TPF() {
    if (speed_factor > delta)
        return speed_factor;
    else
        return delta;
}