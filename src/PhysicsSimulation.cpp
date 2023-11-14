#include "PhysicsSimulation.h"

void PhysicsSimulation::simulate(float deltaTime)
{
	for (RigidBody& rigidBody : rigidBodies)
	{
		if (rigidBody.isAffectedByForces)
		{
			rigidBody.Move(deltaTime);
		}
	}
}

std::vector<RigidBody>& PhysicsSimulation::getRigidBodies()
{
	return rigidBodies;
}

void PhysicsSimulation::addRigidBody(RigidBody& rigidBody)
{
	rigidBodies.push_back(rigidBody);
}

size_t PhysicsSimulation::getRigidBodiesNumber()
{
	return rigidBodies.size();
}