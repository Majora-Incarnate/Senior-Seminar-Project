#ifndef SPATIAL_MAP_H
#define SPATIAL_MAP_H



#include <list>

#include "Object.h"
#include "System.h"



class Spatial_Map
{
public:
	Spatial_Map();
	~Spatial_Map();

	void insert(Object *);
	int search(Object *, int &);

private:
	static const int n;
	static const int max_n;

	static inline int map(float, float);

	std::list<Object *> * lists;
};



#endif