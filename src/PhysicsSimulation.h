#ifndef PHYSICS_SIMULATION_CLASS_H
#define PHYSICS_SIMULATION_CLASS_H

#include "Objects/Object.h"

class PhysicsSimulation
{
public:
	void simulate(float deltaTime, std::vector<Object>& Objects);

	static const glm::vec3 Gravity;

private:
	void HandleCollisions(float deltaTime, std::vector<Object>& Objects);
	bool checkCollision(Object& objectA, Object& objectB);
	bool checkPrimitiveCollision(Object& objectA, Object& objectB);
	bool checkPreciseCollision(Object& objectA, Object& objectB);

	bool checkCollisionCubeCube(Object& cubeA, Object& cubeB);

	std::pair<Face, Face> getClosestFaces(Object& cubeA, Object& cubeB);
};

#endif // !PHYSICS_SIMULATION_CLASS_H
