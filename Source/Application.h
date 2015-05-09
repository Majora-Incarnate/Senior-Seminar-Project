#ifndef APPLICATION_H
#define APPLICATION_H



#include <vector>

#include "Object.h"



class Application {
public:
    Application();
    
    bool Execute();
    
    bool Setup();
    void Cleanup();

    void Events();
    void Loop();
    
private:
    bool is_running;

    int number_of_objects;
    Object * circles;

    double double_for_average;
    double multiprocess_average;
    double quad_tree_average;
    double hilbert_rtree_average;
    int frame_count;

    std::vector<double> dataset[4];
    int dataset_count;
};



#endif
