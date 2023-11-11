#include "PhysicsSimulation.h"

void PhysicsSimulation::simulate()
{

}

std::vector<RigidBody>& PhysicsSimulation::getRigidBodies()
{
	return rigidBodies;
}

void PhysicsSimulation::addRigidBody(RigidBody rigidBody)
{
	rigidBodies.push_back(rigidBody);
}