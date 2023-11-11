#ifndef PHYSICS_SIMULATION_CLASS_H
#define PHYSICS_SIMULATION_CLASS_H

#include "Objects/RigidBody.h"

class PhysicsSimulation
{
public:
	void simulate(float deltaTime);
	std::vector<RigidBody>& getRigidBodies();
	void addRigidBody(RigidBody rigidBody);
	unsigned int getRigidBodiesNumber();

private:
	std::vector<RigidBody> rigidBodies;
};

#endif // !PHYSICS_SIMULATION_CLASS_H
