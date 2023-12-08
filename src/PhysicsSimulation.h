#ifndef PHYSICS_SIMULATION_CLASS_H
#define PHYSICS_SIMULATION_CLASS_H

#include "Objects/Object.h"

class PhysicsSimulation
{
public:
	void simulate(float deltaTime, std::vector<Object>& Objects);

	static const glm::vec3 Gravity;

private:
	void HandleCollisions(float deltaTime, std::vector<Object>& Objects);
	bool checkPrimitiveCollision(Object& objectA, Object& objectB);
};

#endif // !PHYSICS_SIMULATION_CLASS_H
