#include "Collider.h"



const int Collider::NUMBER_OF_CHILDREN = 4;



Collider::Collider()
	: x(0), y(0), r(0)
{
	children = std::vector<Collider *>(NUMBER_OF_CHILDREN);

	for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
		children[i] = NULL;
	
	c.randomize();
	c.a = 0.5f;
}



Collider::Collider(float _x, float _y, float _r)
	: x(_x), y(_y), r(_r)
{
	children = std::vector<Collider *>(NUMBER_OF_CHILDREN);

	for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
		children[i] = NULL;
	
	c.randomize();
	c.a = 0.5f;
}



Collider::~Collider()
{
	if (children[0] != NULL)
		for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
			delete children[i];
}



void Collider::Update(float dx, float dy)
{
	x += dx;
	y += dy;

	if (children[0] != NULL)
		for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
			children[i]->Update(dx, dy);
}

void Collider::Render()
{
	if (children[0] != NULL)
		for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
			children[i]->Render();
	else
		Video_Engine::DrawCircle(x, y, r, &c);
}



void Collider::Subdivide()
{
	if (children[0] == NULL)
	{
		float temp = r / 2.0;
		children[0] = new Collider(x - temp, y, temp);
		children[1] = new Collider(x + temp, y, temp);
		children[2] = new Collider(x, y - temp, temp);
		children[3] = new Collider(x, y + temp, temp);
	}
	else
	{
		for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
			children[i]->Subdivide();
	}
}



bool Collider::Intersects(const Collider * rhs) const
{
	float dx = x - rhs->x;
	float dy = y - rhs->y;
	float dr = r + rhs->r;

	return sqrt(pow(dx, 2) + pow(dy, 2)) <= dr;
	//return dx * dx + dy * dy <= dr * dr;
}



bool Collider::Test(const Collider * rhs) const
{
	if (Intersects(rhs))
	{
		if (children[0] == NULL && rhs->children[0] != NULL)
		{
			for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
				if (rhs->children[i]->Test(this))
				{
					//Video_Engine::DrawCircle(x, y, r, &COLLISION);
					//Video_Engine::DrawCircle(rhs->x, rhs->y, rhs->r, &COLLISION);
					return true;
				}
		}
		else if (children[0] != NULL && rhs->children[0] == NULL)
		{
			for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
				if (children[i]->Test(rhs))
				{
					//Video_Engine::DrawCircle(x, y, r, &COLLISION);
					//Video_Engine::DrawCircle(rhs->x, rhs->y, rhs->r, &COLLISION);
					return true;
				}
		}
		else if (children[0] != NULL && rhs->children[0] != NULL)
		{
			for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
				for (int j = 0; j < NUMBER_OF_CHILDREN; j++)
					if (children[i]->Test(rhs->children[j]))
					{
						//Video_Engine::DrawCircle(x, y, r, &COLLISION);
						//Video_Engine::DrawCircle(rhs->x, rhs->y, rhs->r, &COLLISION);
						return true;
					}
		}
		
		//Video_Engine::DrawCircle(x, y, r, &COLLISION);
		//Video_Engine::DrawCircle(rhs->x, rhs->y, rhs->r, &COLLISION);
		return true;
	}
	
	return false;
}