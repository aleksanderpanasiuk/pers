#include "Object.h"


Object::Object(unsigned int ID, GraphicsComponent& graphicsComponent, RigidBody& rigidBody)
	: graphicsComponent(graphicsComponent),
	rigidBody(rigidBody)
{
	Object::ID = ID;
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

glm::vec3 Object::getPosition()
{
	return rigidBody.getPosition();
}

RigidType Object::getType()
{
	return Object::type;
}


std::vector<std::vector<glm::vec3>> Object::getSides()
{
	switch (type)
	{
	case RigidCube:
		return calculateSidesCube();
		break;
	case RigidSphere:
		break;
	case RigidPlane:
		break;
	default:
		break;
	}

	return std::vector<std::vector<glm::vec3>>();
}

unsigned int Object::getID()
{
	return Object::ID;
}

std::vector<std::vector<glm::vec3>> Object::calculateSidesCube()
{
	glm::vec3 Size = rigidBody.getScale();
	glm::vec3 Position = rigidBody.getPosition();

	std::vector<glm::vec3> verticesPosition = {
		glm::vec3(Position.x - (Size.x / 2), Position.y - (Size.y / 2), Position.z - (Size.z / 2)),
		glm::vec3(Position.x + (Size.x / 2), Position.y - (Size.y / 2), Position.z - (Size.z / 2)),
		glm::vec3(Position.x + (Size.x / 2), Position.y + (Size.y / 2), Position.z - (Size.z / 2)),
		glm::vec3(Position.x - (Size.x / 2), Position.y + (Size.y / 2), Position.z - (Size.z / 2)),
		glm::vec3(Position.x - (Size.x / 2), Position.y - (Size.y / 2), Position.z + (Size.z / 2)),
		glm::vec3(Position.x + (Size.x / 2), Position.y - (Size.y / 2), Position.z + (Size.z / 2)),
		glm::vec3(Position.x + (Size.x / 2), Position.y + (Size.y / 2), Position.z + (Size.z / 2)),
		glm::vec3(Position.x - (Size.x / 2), Position.y + (Size.y / 2), Position.z + (Size.z / 2))
	};

	std::vector<std::vector<glm::vec3>> Sides = {
		{verticesPosition[0], verticesPosition[1], verticesPosition[2], verticesPosition[3]},
		{verticesPosition[4], verticesPosition[5], verticesPosition[6], verticesPosition[7]},
		{verticesPosition[0], verticesPosition[1], verticesPosition[5], verticesPosition[4]},
		{verticesPosition[2], verticesPosition[3], verticesPosition[7], verticesPosition[6]},
		{verticesPosition[0], verticesPosition[3], verticesPosition[7], verticesPosition[4]},
		{verticesPosition[1], verticesPosition[2], verticesPosition[6], verticesPosition[5]}
	};

	return Sides;
}

