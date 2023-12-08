#include "PhysicsSimulation.h"

const glm::vec3 PhysicsSimulation::Gravity = glm::vec3(0.0f, -9.81f, 0.0f);

void PhysicsSimulation::simulate(float deltaTime, std::vector<Object>& Objects)
{
	HandleCollisions(deltaTime, Objects);

	for (Object& object : Objects)
	{
		// calcualte movement
		object.Update(deltaTime);
	}
}

void PhysicsSimulation::HandleCollisions(float deltaTime, std::vector<Object>& Objects)
{
	int numberOfObjects = Objects.size();

	for (int i = 0; i < numberOfObjects; i++)
	{
		for (int j = i + 1; j < numberOfObjects; j++)
		{
			Object& objectA = Objects[i];
			Object& objectB = Objects[j];

			if (checkCollision(objectA, objectB))
			{
				std::cout << "!Collision!: " << objectA.getName() << " <> " << objectB.getName() << "\n";
			}
		}
	}
}

bool PhysicsSimulation::checkCollision(Object& objectA, Object& objectB)
{
	if (checkPrimitiveCollision(objectA, objectB))
		return checkPreciseCollision(objectA, objectB);

	return false;
}

bool PhysicsSimulation::checkPreciseCollision(Object& objectA, Object& objectB)
{
	return true;
}

bool PhysicsSimulation::checkPrimitiveCollision(Object& objectA, Object& objectB)
{
	float distanceBetweenObjects = glm::distance(objectA.getPosition(), objectB.getPosition());
	float radiiSum = objectA.getRigidBody().getBoundingSphereRadius() +
		objectB.getRigidBody().getBoundingSphereRadius();

	return radiiSum >= distanceBetweenObjects;
}
