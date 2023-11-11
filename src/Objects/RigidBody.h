#ifndef RIGID_BODY_CLASS_H
#define RIGID_BODY_CLASS_H

#include <glm/glm.hpp>
#include <vector>

#include "RigidBodyType.h"

class RigidBody
{
public:
	RigidBody(Type type, glm::vec3 Position);

	void changePosition(glm::vec3 newPosition);
	void Move(float deltaTime, glm::vec3 positionChange);
	void Rotate(float deltaTime, glm::vec3 rotationChange);
	void Rescale(glm::vec3 newScale);

	glm::vec3 getPosition();
	glm::vec3 getOrientation();
	glm::vec3 getScale();
	Type getType();

private:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	Type type;
};

#endif // !RIGID_BODY_CLASS_H
