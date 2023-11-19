#include "Object.h"


Object::Object(GraphicsComponent& graphicsComponent, RigidBody& rigidBody)
	: graphicsComponent(graphicsComponent),
	rigidBody(rigidBody)
{
	Object::type = rigidBody.getType();
}

void Object::Update(float deltaTime)
{
	rigidBody.Move(deltaTime);
}

void Object::Render(Shader& shader, Camera& camera)
{
	graphicsComponent.Draw(
		shader, camera,
		rigidBody.getPosition(),
		rigidBody.getOrientation(),
		rigidBody.getScale()
	);
}

GraphicsComponent& Object::getGraphicsComponent()
{
	return graphicsComponent;
}

RigidBody& Object::getRigidBody()
{
	return rigidBody;
}

RigidType Object::getType()
{
	return Object::type;
}
