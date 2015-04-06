#ifndef COLLIDER_H
#define COLLIDER_H



#include <vector>

#include "Color.h"
#include "Video_Engine.h"



class Collider
{
public:
	float x, y, r;
	Color c;

	std::vector<Collider *> children;

	Collider();
	Collider(float, float, float);
	~Collider();

	void Update(float, float);
	void Render();
	void Subdivide();
	bool Intersects(const Collider *) const;
	bool Test(const Collider *) const;
	
	static bool DRAW_COLLIDING_OBJECTS;

private:
	static const int NUMBER_OF_CHILDREN;
};



#endif