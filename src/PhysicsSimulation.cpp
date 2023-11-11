#include "PhysicsSimulation.h"

void PhysicsSimulation::simulate(float deltaTime)
{
	for (RigidBody& rigidBody : rigidBodies)
	{
		rigidBody.Move(deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
		rigidBody.Rotate(deltaTime, glm::vec3(0.0f, 0.0f, -50.0f));
	}
}

std::vector<RigidBody>& PhysicsSimulation::getRigidBodies()
{
	return rigidBodies;
}

void PhysicsSimulation::addRigidBody(RigidBody rigidBody)
{
	rigidBodies.push_back(rigidBody);
}