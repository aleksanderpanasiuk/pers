#ifndef RIGID_BODY_CLASS_H
#define RIGID_BODY_CLASS_H

#include <glm/glm.hpp>
#include <vector>


enum RigidType { RigidCube, RigidSphere, RigidPlane };


class RigidBody
{
public:
	RigidBody(
		RigidType type,
		glm::vec3 Position, 
		glm::vec3 Orientation, 
		glm::vec3 Scale, 
		bool isAffectedByForces,
		float mass
	);

	void changePosition(glm::vec3 newPosition);
	void Move(float deltaTime);
	void Rotate(float deltaTime, glm::vec3 rotationChange);
	void Rescale(glm::vec3 newScale);

	void setVelocity(glm::vec3 Velocity);
	void Accelerate(glm::vec3 Acceleration, float deltaTime);

	glm::vec3 getVelocity();
	glm::vec3 getPosition();
	glm::vec3 getOrientation();
	glm::vec3 getScale();
	RigidType getType();

	bool isAffectedByForces = true;

private:
	RigidType type;

	float Mass = 1.0f;

	glm::vec3 Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

#endif // !RIGID_BODY_CLASS_H
