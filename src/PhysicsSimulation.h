#ifndef PHYSICS_SIMULATION_CLASS_H
#define PHYSICS_SIMULATION_CLASS_H

#include "Objects/Object.h"

class PhysicsSimulation
{
public:
	void simulate(float deltaTime, std::vector<Object>& Objects);

	const glm::vec3 Gravity = glm::vec3(0.0f, -9.81f, 0.0f);
};

#endif // !PHYSICS_SIMULATION_CLASS_H
