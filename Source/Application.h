#ifndef APPLICATION_H
#define APPLICATION_H



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
    double quad_tree_average;
    int double_for_count;
    int quad_tree_count;
};



#endif
