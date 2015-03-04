#ifndef TIMER_H
#define TIMER_H



class Timer {
public:
	Timer();
	Timer(float);

	void Start();
	bool Ended();

	void Update(float);

	void Set_Interval(float);
	void Set_Progress(float);
	float Get_Interval();
	float Get_Progress();

private:
	bool active;
	
	float timer;
	float interval;
};



#endif