#include "HR_Tree.h"
#include "BTree.h"



const int HR_Tree::n = 32;



HR_Tree::HR_Tree()
{
	lists = new std::list<Object *>[n * n];
}



HR_Tree::~HR_Tree()
{
	delete[] lists;
}



void HR_Tree::insert(Object * other)
{
	/*int start = map(other->x - other->r, other->y - other->r);
	int line = map(other->x + other->r, other->y - other->r);
	int end = map(other->x + other->r, other->y + other->r);

	for (int i = start; i <= end; i++)
	{
		if (i > line)
		{
			start += n;
			line += n;
			i = start;
		}

		lists[i].push_front(other);
	}*/
	lists[map(other->x - other->r, other->y - other->r)].push_front(other);
	lists[map(other->x + other->r, other->y - other->r)].push_front(other);
	lists[map(other->x - other->r, other->y + other->r)].push_front(other);
	lists[map(other->x + other->r, other->y + other->r)].push_front(other);
}



int HR_Tree::search(Object * other, int & c)
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



inline int HR_Tree::map(float x, float y)
{
	int dy = (int(y * n) / System::window_height) >= n ? (n - 1) * n : (int(y * n) / System::window_height) * n;
	int dx = (int(x * n) / System::window_width) >= n ? (n - 1) : (int(x * n) / System::window_width);

	return dy + dx;
}