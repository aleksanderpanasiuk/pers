#ifndef PHYSICS_SIMULATION_CLASS_H
#define PHYSICS_SIMULATION_CLASS_H

#include "Objects/Object.h"

class PhysicsSimulation
{
public:
	void simulate(float deltaTime, std::vector<Object>& Objects);

	static const glm::vec3 Gravity;
};

#endif // !PHYSICS_SIMULATION_CLASS_H
