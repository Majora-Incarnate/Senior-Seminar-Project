#ifndef PH_TREE_H
#define PH_TREE_H



#include <list>
#include <bitset>

#include "Object.h"



int float_to_raw_int(float value)
{
	union
	{
		float f;  // assuming 32-bit IEEE 754 single-precision
		int i;    // assuming 32-bit 2's complement int
	} u;

	u.f = x;
	return u.i;
}



struct PH_Entry
{
	std::list<bool> x_prefix;
	std::list<bool> y_prefix;
	Object * object;	
};



class PH_Node
{
public:
	PH_Node();
	~PH_Node();

	void insert();
	void search();

private:
	std::list<bool> x_prefix;
	std::list<bool> y_prefix;

	std::list<PH_Entry> entries;

	PH_Node * children[4];

	static const int NUMBER_OF_CHILDREN;
};



const int PH_Node::NUMBER_OF_CHILDREN = 4;



PH_Node::PH_Node()
{
	for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
		children[i] = NULL;
}



PH_Node::~PH_Node()
{
	for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
		if (children[i] != NULL)
			delete children[i];
}



#endif