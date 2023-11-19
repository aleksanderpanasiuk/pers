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

std::vector<glm::vec3> Object::getVertices()
{
	switch (type)
	{
	case RigidCube:
		return calculateVerticesCube();
		break;
	case RigidSphere:
		break;
	case RigidPlane:
		break;
	default:
		break;
	}

	return std::vector<glm::vec3>();
}

std::vector<glm::vec3> Object::calculateVerticesCube()
{
	glm::vec3 Position = rigidBody.getPosition();
	glm::vec3 Size = rigidBody.getScale();

	std::vector<glm::vec3> Vertices = {
		glm::vec3(Position.x - (Size.x / 2), Position.y - (Size.y / 2), Position.z - (Size.z / 2)),
		glm::vec3(Position.x - (Size.x / 2), Position.y - (Size.y / 2), Position.z + (Size.z / 2)),
		glm::vec3(Position.x - (Size.x / 2), Position.y + (Size.y / 2), Position.z - (Size.z / 2)),
		glm::vec3(Position.x - (Size.x / 2), Position.y + (Size.y / 2), Position.z + (Size.z / 2)),
		glm::vec3(Position.x + (Size.x / 2), Position.y - (Size.y / 2), Position.z - (Size.z / 2)),
		glm::vec3(Position.x + (Size.x / 2), Position.y - (Size.y / 2), Position.z + (Size.z / 2)),
		glm::vec3(Position.x + (Size.x / 2), Position.y + (Size.y / 2), Position.z - (Size.z / 2)),
		glm::vec3(Position.x + (Size.x / 2), Position.y + (Size.y / 2), Position.z + (Size.z / 2))
	};

	return Vertices;
}
