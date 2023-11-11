#include "RigidBody.h"

RigidBody::RigidBody(Type type, glm::vec3 Position)
{
	RigidBody::Position = Position;
	RigidBody::type = type;
}

void RigidBody::Move(float deltaTime, glm::vec3 poistionChange)
{
	Position = Position + (deltaTime * poistionChange);
}

void RigidBody::changePosition(glm::vec3 newPosition)
{
	Position = newPosition;
}

void RigidBody::Rotate(float deltaTime, glm::vec3 rotationChange)
{
	Orientation += rotationChange * deltaTime;
}

void RigidBody::Rescale(glm::vec3 newScale)
{
	Scale = newScale;
}

glm::vec3 RigidBody::getPosition()
{
	return Position;
}

glm::vec3 RigidBody::getOrientation()
{
	return Orientation;
}

glm::vec3 RigidBody::getScale()
{
	return Scale;
}

Type RigidBody::getType()
{
	return type;
}