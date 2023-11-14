#include "PhysicsSimulation.h"

void PhysicsSimulation::simulate(float deltaTime, std::vector<Object>& Objects)
{
	for (Object& object : Objects)
	{
		object.Update(deltaTime);
	}
}
