#include "Quad_Tree.h"



const int Quad_Tree::subdivision_count = 4;
const int Quad_Tree::depth_limit = 5;
const int Quad_Tree::item_limit = 4;



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



Quad_Tree::~Quad_Tree()
{
	if (divisions[0] != NULL)
		for (int i = 0; i < subdivision_count; i++)
			delete divisions[i];

	delete[] divisions;
}



void Quad_Tree::Subdivide()
{
	divisions[0] = new Quad_Tree(x, 			y, 				(w / 2.0), 	(h / 2.0),	depth + 1, 0);
	divisions[1] = new Quad_Tree(x + (w / 2.0), y, 				(w / 2.0), 	(h / 2.0),	depth + 1, 1);
	divisions[2] = new Quad_Tree(x + (w / 2.0), y + (h / 2.0), 	(w / 2.0), 	(h / 2.0),	depth + 1, 2);
	divisions[3] = new Quad_Tree(x, 			y + (h / 2.0), 	(w / 2.0), 	(h / 2.0),	depth + 1, 3);

	std::list<Object *> temp(objects);
	objects.clear();

	for (std::list<Object *>::iterator it = temp.begin(); it != temp.end(); ++it)
		Insert(*it);
}



bool Quad_Tree::Within(const Object * other) const
{
	return 	other->x - other->r > x 	&&
			other->x + other->r < x + w &&
			other->y - other->r > y 	&&
			other->y + other->r < y + h;
}



bool Quad_Tree::Intersects(const Object * other) const
{
	return !((other->x + other->r < x || other->x - other->r > x + w) && (other->y + other->r < y || other->y - other->r > y + h));
}



void Quad_Tree::Insert(Object * other)
{
	if (divisions[0] == NULL)
	{
		objects.push_front(other);

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
			objects.push_front(other);
	}
}



int Quad_Tree::Test(Object * other)
{
	objects.remove(other);

	int temp = 0;

	if (divisions[0] != NULL)
		for (int i = 0; i < subdivision_count; i++)
			if (divisions[i]->Intersects(other))
				temp += divisions[i]->Test(other);

	for (std::list<Object *>::iterator it = objects.begin(); it != objects.end(); ++it)
		if (other->Intersects(**it))
			temp++;

	return temp;
}



void Quad_Tree::Render()
{
	Video_Engine::DrawRect(x, y, w, h, &c);

	if (divisions[0] != NULL)
		for (int i = 0; i < subdivision_count; i++)
			divisions[i]->Render();
}