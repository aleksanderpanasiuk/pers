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

bool PhysicsSimulation::checkCollisionCubeCube(Object& cubeA, Object& cubeB)
{
	
}

std::pair<Face, Face> PhysicsSimulation::getClosestFaces(Object& cubeA, Object& cubeB)
{
	std::vector<Face> facesA = cubeA.getRigidBody().getFaces();
	std::vector<Face> facesB = cubeB.getRigidBody().getFaces();

	float minDistance = 10 * glm::distance(cubeA.getPosition(), cubeB.getPosition());
	int minFaceA = 0;
	int minFaceB = 0;

	for (int i = 0; i < facesA.size(); i++)
	{
		Face faceA = facesA[i];

		for (int j = 0; j < facesB.size(); j++)
		{
			Face faceB = facesB[j];

			float distance = glm::distance(faceA.getMiddlePoint(), faceB.getMiddlePoint());

			if (distance <= minDistance)
			{
				minDistance = distance;
				minFaceA = i;
				minFaceB = j;
			}
		}
	}

	return std::make_pair(facesA[minFaceA], facesB[minFaceB]);
}

bool PhysicsSimulation::checkPreciseCollision(Object& objectA, Object& objectB)
{
	if (objectA.getType() == RigidCube and objectB.getType() == RigidCube)
		return checkCollisionCubeCube(objectA, objectB);

	return false;
}

bool PhysicsSimulation::checkPrimitiveCollision(Object& objectA, Object& objectB)
{
	float distanceBetweenObjects = glm::distance(objectA.getPosition(), objectB.getPosition());
	float radiiSum = objectA.getRigidBody().getBoundingSphereRadius() +
		objectB.getRigidBody().getBoundingSphereRadius();

	return radiiSum >= distanceBetweenObjects;
}
