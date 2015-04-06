#ifndef CONFIG_H
#define CONFIG_H



struct Config
{
	static const int NUMBER_OF_THREADS;
	static const int NUMBER_OF_OBJECTS;
	static const bool PRINT_DOUBLE_FOR_AVERAGE;
	static const bool PRINT_MULTITHREAD_AVERAGE;
	static const bool PRINT_QUADTREE_AVERAGE;
	static const bool PRINT_SPATIAL_MAP_AVERAGE;
	static const bool PRINT_DOUBLE_FOR_FRAME;
	static const bool PRINT_MULTITHREAD_FRAME;
	static const bool PRINT_QUADTREE_FRAME;
	static const bool PRINT_SPATIAL_MAP_FRAME;
	static const bool DRAW_QUADTREE;
};



#endif