#include "Spatial_Map.h"
#include "BTree.h"



const int Spatial_Map::n = 16;
const int Spatial_Map::max_n = 16;



Spatial_Map::Spatial_Map()
{
	lists = new std::list<Object *>[n * n];
}



Spatial_Map::~Spatial_Map()
{
	delete[] lists;
}



void Spatial_Map::insert(Object * other)
{
	lists[map(other->x - other->r, other->y - other->r)].push_front(other);
	lists[map(other->x + other->r, other->y - other->r)].push_front(other);
	lists[map(other->x - other->r, other->y + other->r)].push_front(other);
	lists[map(other->x + other->r, other->y + other->r)].push_front(other);
}



int Spatial_Map::search(Object * other, int & c)
{
	int start = map(other->x - other->r, other->y - other->r);
	int line = map(other->x + other->r, other->y - other->r);
	int end = map(other->x + other->r, other->y + other->r);
	int temp = 0;

	SelfBalancingBinarySearchTree bsttree;

	for (int i = start; i <= end; i++)
	{
		if (i > line)
		{
			start += n;
			line += n;
			i = start;
		}

		lists[i].remove(other);

		for (std::list<Object *>::iterator it = lists[i].begin(); it != lists[i].end(); ++it)
		{
			c++;

			if (other->Intersects(**it))
			{
				if (!bsttree.search(*it))
				{
					bsttree.insert(*it);
					temp++;
				}
			}
		}
	}

	return temp;
}



inline int Spatial_Map::map(float x, float y)
{
	int dy = (int(y * n) / System::window_height) >= n ? (n - 1) * n : (int(y * n) / System::window_height) * n;
	int dx = (int(x * n) / System::window_width) >= n ? (n - 1) : (int(x * n) / System::window_width);

	return dy + dx;
}