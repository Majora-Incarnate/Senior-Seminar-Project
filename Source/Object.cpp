#include "Clock.h"
#include "Math.h"
#include "Object.h"



Object::Object()
{
	x = rand() % System::window_width;
	y = rand() % System::window_height;
	r = rand() % 10 + 10;
	v = rand() % 20 + 20;
	a = rand() % 360;
	c.randomize();
	c.a = 0.5f;
}



bool Object::Intersects(const Object & rhs) const {
	float dx = x + r - rhs.x + rhs.r;
	float dy = y + r - rhs.y + rhs.r;
	float dr = r + rhs.r;

	return dx * dx + dy * dy <= dr * dr;
}



void Object::Update()
{
	x += v * sin(a * PI / 180) * Clock::Frame_Control.Get_TPF();
	y += v * cos(a * PI / 180) * Clock::Frame_Control.Get_TPF();

	if (x < 0.0f)
	{
		x = 0.0f - x;
		a = 270.0f - (a - 90.0f);
		a = (int)a % 360;
	}
	if (x > System::window_width)
	{
		x = System::window_width - (x - System::window_width);
		a = 90.0f - (a - 270.0f);
		a = (int)a % 360;
	}
	if (y < 0.0f)
	{
		y = 0.0f - y;
		a = 360.0f - (a - 180.0f);
		a = (int)a % 360;
	}
	if (y > System::window_height)
	{
		y = System::window_height - (y - System::window_height);
		a = 180.0f - (a - 360.0f);
		a = (int)a % 360;
	}
}



void Object::Render()
{
	Video_Engine::DrawCircle(x, y, r, &c);
}