#include "Cube.h"

Cube::Cube(Shader& shader, glm::vec3 Position, float sideLength)
{
	Cube::shader = &shader;
	Cube::Position = Position;
	Cube::sideLength = sideLength;

	mesh.setData(Vertices, Indices);
}

void Cube::Draw(Camera& camera)
{
	if (not isVisible)
		return;

	mesh.Draw(*shader, camera, Position, Orientation, Scale);
}

void Cube::Move(glm::vec3 poistionChange)
{
	Position = Position + poistionChange;
}

void Cube::changePosition(glm::vec3 newPosition)
{
	Position = newPosition;
}

void Cube::Rotate(glm::vec3 rotationChange)
{
	Orientation += rotationChange;
}