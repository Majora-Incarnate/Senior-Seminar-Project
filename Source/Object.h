#ifndef OBJECT_H
#define OBJECT_H



#include "Color.h"
#include "Video_Engine.h"



class Object
{
public:
	float x, y, r, v, a;
	Color c;

	Object();

	void Update();
	void Render();
	bool Intersects(const Object &) const;
private:
};



#endif