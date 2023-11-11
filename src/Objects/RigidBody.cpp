#include "RigidBody.h"

RigidBody::RigidBody(unsigned int ID, RigidType type, 
	glm::vec3 Position, glm::vec3 Orientation, glm::vec3 Scale)
{
	RigidBody::ID = ID;
	RigidBody::Position = Position;
	RigidBody::Orientation = Orientation;
	RigidBody::Scale = Scale;
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

unsigned int RigidBody::getID()
{
	return ID;
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

RigidType RigidBody::getType()
{
	return type;
}