#ifndef OBJECT_H
#define OBJECT_H



#include "Color.h"
#include "Video_Engine.h"
#include "Collider.h"



class Object
{
public:
	float x, y, r, v, a;
	Color c;
	Collider b;

	Object();

	void Update();
	void Render();
	bool Intersects(const Object &) const;
private:
};



#endif