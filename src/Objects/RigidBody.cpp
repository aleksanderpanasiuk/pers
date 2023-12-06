#include "RigidBody.h"

RigidBody::RigidBody(
	RigidType type,
	glm::vec3 Position,
	glm::vec3 Orientation,
	glm::vec3 Scale,
	bool isAffectedByForces,
	float mass
)
{
	RigidBody::Position = Position;
	RigidBody::Orientation = Orientation;
	RigidBody::Scale = Scale;
	RigidBody::type = type;
	RigidBody::isAffectedByForces = isAffectedByForces;
	RigidBody::Mass = (mass == 0.0f ? Scale.x* Scale.y* Scale.z : mass);

	// apply standard gravity
	applyForce(mass * glm::vec3(0.0f, -9.81f, 0.0f));
}

void RigidBody::Move(float deltaTime)
{
	if (isAffectedByForces)
	{
		Velocity += (NetForce / Mass) * deltaTime;
	}

	Position += (deltaTime * Velocity);
}

void RigidBody::changePosition(glm::vec3 newPosition)
{
	Position = newPosition;
}

void RigidBody::changeOrientation(glm::vec3 newOrientation)
{
	RigidBody::Orientation = newOrientation;
}

void RigidBody::Rotate(float deltaTime, glm::vec3 rotationChange)
{
	Orientation += rotationChange * deltaTime;
}

void RigidBody::Rescale(glm::vec3 newScale)
{
	Scale = newScale;
}

void RigidBody::setVelocity(glm::vec3 Velocity)
{
	RigidBody::Velocity = Velocity;
}

void RigidBody::applyForce(glm::vec3 Force)
{
	NetForce += Force;
}

glm::vec3 RigidBody::getVelocity()
{
	return Velocity;
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

float RigidBody::getMass()
{
	return Mass;
}