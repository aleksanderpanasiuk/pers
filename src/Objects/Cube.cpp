#include "Cube.h"

Cube::Cube(Shader& shader, glm::vec3 Position, float sideLength, glm::vec3 Color) :
	Rectangle(shader, Position, glm::vec3(sideLength, sideLength, sideLength), Color)
{
	Cube::sideLength = sideLength;
	Rectangle::Color = glm::vec3(0.5f, 0.2f, 0.2f);
}
