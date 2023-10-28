#include "Cube.h"

Cube::Cube(Shader& shader, glm::vec3 Position, float sideLength) :
	Rectangle(shader, Position, glm::vec3(sideLength, sideLength, sideLength))
{
	Cube::sideLength = sideLength;
	Rectangle::Color = glm::vec3(0.5f, 0.2f, 0.2f);
}
