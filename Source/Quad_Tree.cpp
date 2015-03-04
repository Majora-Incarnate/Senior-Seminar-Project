#include "Quad_Tree.h"



const int Quad_Tree::subdivision_count = 4;
const int Quad_Tree::depth_limit = 4;
const int Quad_Tree::item_limit = 16;



Quad_Tree::Quad_Tree(float _x, float _y, float _w, float _h, int d, int id)
	: x(_x), y(_y), w(_w), h(_h), depth(d)
{
	divisions = new Quad_Tree * [subdivision_count];

	for (int i = 0; i < subdivision_count; i++)
		divisions[i] = NULL;

	c.a = 0.5f;

	switch(id)
	{
	case 0:
		c.r = 0.25f * (d + 1);
		c.g = 0.0f;
		c.b = 0.0f;
		break;
	case 1:
		c.r = 0.25f * (d + 1);
		c.g = 0.125f * (d + 1);
		c.b = 0.0f;
		break;
	case 2:
		c.r = 0.0f;
		c.g = 0.25f * (d + 1);
		c.b = 0.0f;
		break;
	case 3:
		c.r = 0.0f;
		c.g = 0.0f;
		c.b = 0.25f * (d + 1);
		break;
	default:
		c.a = 0.0f;
		c.r = 0.0f;
		c.g = 0.0f;
		c.b = 0.0f;
	}
}



void Quad_Tree::Subdivide()
{
	//Northwest
	//Northeast
	//Southeast
	//Southwest
	divisions[0] = new Quad_Tree(x, 			y, 				x + (w / 2.0), 	y + (h / 2.0),	depth + 1, 0);
	divisions[1] = new Quad_Tree(x + (w / 2.0), y, 				x + w, 			y + (h / 2.0),	depth + 1, 1);
	divisions[2] = new Quad_Tree(x + (w / 2.0), y + (h / 2.0), 	x + w, 			y + h,			depth + 1, 2);
	divisions[3] = new Quad_Tree(x, 			y + (h / 2.0), 	x + (w / 2.0), 	y + h,			depth + 1, 3);

	std::list<Object *> temp(objects);
	objects.clear();

	while(!temp.empty())
	{
		Insert(temp.front());
		temp.pop_front();
	}
}



bool Quad_Tree::Within(const Object * other) const
{
	return !((other->x < x || other->x > x + w) & (other->y < y || other->y > y + h));
}



void Quad_Tree::Insert(Object * other)
{
	if (divisions[0] == NULL)
	{
		objects.push_back(other);

		if (objects.size() >= Quad_Tree::item_limit && depth + 1 < Quad_Tree::depth_limit)
			Subdivide();
	}
	else
	{
		if (divisions[0]->Within(other))
			divisions[0]->Insert(other);
		else if (divisions[1]->Within(other))
			divisions[1]->Insert(other);
		else if (divisions[2]->Within(other))
			divisions[2]->Insert(other);
		else if (divisions[3]->Within(other))
			divisions[3]->Insert(other);
		else
			objects.push_back(other);
	}
}



std::list<Object *> Quad_Tree::Test(Object * other)
{
	if (divisions[0] != NULL)
		for (int i = 0; i < subdivision_count; i++)
			if (divisions[i]->Within(other))
				return divisions[i]->Test(other);

	return objects;
}



void Quad_Tree::Render()
{
	Video_Engine::DrawRect(x, y, w, h, &c);

	if (divisions[0] != NULL)
		for (int i = 0; i < subdivision_count; i++)
			divisions[i]->Render();
}