#include "PhysicsSimulation.h"

void PhysicsSimulation::simulate(float deltaTime, std::vector<Object>& Objects)
{
	for (Object& object : Objects)
	{
		// calcualte movement
		object.Update(deltaTime);
	}
}
