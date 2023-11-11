#ifndef RIGID_BODY_CLASS_H
#define RIGID_BODY_CLASS_H

#include <glm/glm.hpp>

class RigidBody
{
public:
	void Move(float deltaTime, glm::vec3 positionChange);
	void Rotate(float deltaTime, glm::vec3 rotationChange);
	void Rescale(glm::vec3 newScale);

	glm::vec3 getPosition();

private:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

#endif // !RIGID_BODY_CLASS_H