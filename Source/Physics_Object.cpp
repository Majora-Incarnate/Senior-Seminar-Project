#include "Physics_Object.h"



std::deque<Physics_Object *> Physics_Object::objects;



void Physics_Object::Set_Inertia(float radius) {
	inertia = (2.0 * mass * radius * radius) / 3.0;
}

void Physics_Object::Apply_Force(float new_force, float new_angle, float _x, float _y) {
	new_angle = new_angle * PI / 180;
    force += new_force;
    torque += ((_x * new_force * cos(new_angle)) + (_y * new_force * sin(new_angle)));
}

void Physics_Object::Apply_Torque(float new_torque) {
    torque += new_torque;
}

void Physics_Object::Calculate_Velocity(double dt) {
	velocity += (force / mass) * dt;
	force = 0.0;
}

void Physics_Object::Calculate_Rotation(double dt) {
	rotation += (torque / inertia) * dt;
	torque = 0.0;
}

void Physics_Object::Calculate_Vector(double dt) {
	/*angle += rotation * dt;

	dx = velocity * cos(angle * PI / 180) * dt;
	dy = velocity * sin(angle * PI / 180) * dt;*/
}

void Physics_Object::Move(double dt) {
	x += dx;
	y -= dy;
}