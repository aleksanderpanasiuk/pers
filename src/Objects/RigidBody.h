#ifndef RIGID_BODY_CLASS_H
#define RIGID_BODY_CLASS_H

#include <glm/glm.hpp>
#include <vector>


enum RigidType { RigidCube, RigidSphere, RigidPlane };


class RigidBody
{
public:
	RigidBody(unsigned int ID, RigidType type,
		glm::vec3 Position, glm::vec3 Orientation, glm::vec3 Scale, 
		bool isAffectedByForces);

	void changePosition(glm::vec3 newPosition);
	void Move(float deltaTime, glm::vec3 positionChange);
	void Rotate(float deltaTime, glm::vec3 rotationChange);
	void Rescale(glm::vec3 newScale);

	unsigned int getID();
	glm::vec3 getPosition();
	glm::vec3 getOrientation();
	glm::vec3 getScale();
	RigidType getType();

	bool isAffectedByForces = true;

private:
	unsigned int ID;
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	RigidType type;
};

#endif // !RIGID_BODY_CLASS_H
