#include "Timer.h"



Timer::Timer()
	: timer(0), interval(0), active(false) {}

Timer::Timer(float _timer)
	: timer(_timer), interval(_timer), active(false) {}

void Timer::Start() {
	active = true;
	timer = 0;
}

bool Timer::Ended() {
	return !active;
}

void Timer::Update(float dt) {
	if (active)
		timer += dt;
	if (timer >= interval)
		active = false;
}

void Timer::Set_Interval(float _interval) {
	interval = _interval;
}

void Timer::Set_Progress(float progress) {
	timer = interval * (progress > 1 ? 1 : (progress < 0 ? 0 : progress));
}

float Timer::Get_Interval() {
	return interval;
}

float Timer::Get_Progress() {
	return (timer / interval);
}