#include "PhysicsSimulation.h"

const glm::vec3 PhysicsSimulation::Gravity = glm::vec3(0.0f, -9.81f, 0.0f);

void PhysicsSimulation::simulate(float deltaTime, std::vector<Object>& Objects)
{
	for (Object& object : Objects)
	{
		// calcualte movement
		object.Update(deltaTime);
	}
}
