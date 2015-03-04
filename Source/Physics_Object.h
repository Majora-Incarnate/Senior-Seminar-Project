#ifndef PHYSICS_OBJECTS_H
#define PHYSICS_OBJECTS_H



#include <deque>
#include <cmath>

#include "World_Object.h"
#include "Math.h"



static const float DEFAULT_FRICTION_COEFFICIENT = 0.96;



class Physics_Object : virtual public World_Object {
public:
	void Set_Inertia(float);
	void Apply_Force(float, float, float, float);
	void Apply_Torque(float);
	void Calculate_Velocity(double);
	void Calculate_Rotation(double);
	void Calculate_Vector(double);
	void Move(double);
    
	virtual void Apply(double) = 0;

    float mass;
    float force;

    float velocity;

    float inertia;
    float torque;

    float rotation;
    float fritction;

    float dx, dy;

    static std::deque<Physics_Object *> objects;

private:
};



#endif