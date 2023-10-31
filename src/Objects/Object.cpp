#include "Object.h"

Object::Object(Shader& shader)
{
	Object::shader = &shader;
}

void Object::Draw(Camera& camera)
{
	if (isVisible)
	{
		mesh.Draw(*shader, camera, Position, Orientation, Scale);
	}
}

void Object::changeColor(glm::vec3 Color)
{
	Object::Color = Color;
}

void Object::Move(float deltaTime, glm::vec3 poistionChange)
{
	Position = Position + (deltaTime * poistionChange);
}

void Object::changePosition(glm::vec3 newPosition)
{
	Position = newPosition;
}

void Object::Rotate(glm::vec3 rotationChange)
{
	Orientation += rotationChange;
}

void Object::Rescale(glm::vec3 newScale)
{
	Scale = newScale;
}

glm::vec3 Object::getPosition()
{
	return Object::Position;
}


