#ifndef HR_TREE_H
#define HR_TREE_H



#include <list>

#include "Object.h"
#include "System.h"



class HR_Tree
{
public:
	HR_Tree();
	~HR_Tree();

	void insert(Object *);
	int search(Object *, int &);

private:
	static const int n;

	static inline int map(float, float);

	std::list<Object *> * lists;
};



#endif