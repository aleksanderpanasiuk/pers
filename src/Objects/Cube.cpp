#include "Cube.h"

Cube::Cube(Shader& shader, glm::vec3 Position, float sideLength, glm::vec3 Color) :
	Cuboid(shader, Position, glm::vec3(sideLength, sideLength, sideLength), Color)
{
	Cube::sideLength = sideLength;
}
