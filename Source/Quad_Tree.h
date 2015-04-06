#ifndef QUAD_TREE_H
#define QUAD_TREE_H



#include <list>

#include "Color.h"
#include "Video_Engine.h"
#include "Object.h"



class Quad_Tree
{
public:
	Quad_Tree(float, float, float, float, int = 0, int = -1);
	~Quad_Tree();

	void Subdivide();
	bool Within(const Object *) const;
	bool Intersects(const Object *) const;
	void Insert(Object *);
	int Test(Object *, int &);

	void Render();

private:
	static const int subdivision_count;
	static const int depth_limit;
	static const int item_limit;

	Quad_Tree ** divisions;
	float x, y, w, h;
	int depth;
	Color c;
	std::list<Object *> objects;
};



#endif