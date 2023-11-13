#include "PhysicsSimulation.h"

void PhysicsSimulation::simulate(float deltaTime)
{
	for (RigidBody& rigidBody : rigidBodies)
	{
		if (rigidBody.isAffectedByForces)
		{
			rigidBody.Move(deltaTime);
			rigidBody.Rotate(deltaTime, glm::vec3(0.0f, 0.0f, -50.0f));
		}
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

unsigned int PhysicsSimulation::getRigidBodiesNumber()
{
	return rigidBodies.size();
}