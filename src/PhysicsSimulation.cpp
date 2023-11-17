#include "PhysicsSimulation.h"

void PhysicsSimulation::simulate(float deltaTime, std::vector<Object>& Objects)
{
	for (Object& object : Objects)
	{
		// apply gravity
		object.getRigidBody().Accelerate(Gravity, deltaTime);

		// calcualte movement
		object.Update(deltaTime);
	}
}
