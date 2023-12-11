#include "Object.h"


Object::Object(unsigned int ID, GraphicsComponent& graphicsComponent, RigidBody& rigidBody)
	: graphicsComponent(graphicsComponent),
	rigidBody(rigidBody)
{
	Object::ID = ID;
	Object::type = rigidBody.getType();

	Object::Name = "";

	switch (rigidBody.getType())
	{
	case RigidCube:
		Object::Name = "Cube";
		break;
	case RigidSphere:
		Object::Name = "Sphere";
		break;
	case RigidPlane:
		Object::Name = "Plane";
		break;
	default:
		Object::Name = "Object";
		break;
	}

	Object::Name += " " + std::to_string(ID);
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

glm::vec3 Object::getPosition()
{
	return rigidBody.getPosition();
}

glm::vec3 Object::getVelocity()
{
	return rigidBody.getVelocity();
}

void Object::setPosition(glm::vec3 Position)
{
	rigidBody.changePosition(Position);
}

void Object::setVelocity(glm::vec3 Velocity)
{
	rigidBody.setVelocity(Velocity);
}

RigidType Object::getType()
{
	return Object::type;
}

unsigned int Object::getID()
{
	return Object::ID;
}

std::string Object::getName()
{
	return Name;
}

void Object::setName(std::string name)
{
	Object::Name = name;
}

glm::vec3 Object::getColor()
{
	return graphicsComponent.getColor();
}

void Object::changeColor(glm::vec3 Color)
{
	graphicsComponent.ChangeColor(Color);
}
