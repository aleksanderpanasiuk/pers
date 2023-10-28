#include "Cube.h"

Cube::Cube(Shader& shader, glm::vec3 Position, float sideLength) :
	Object(shader)
{
	changePosition(Position);
	Cube::sideLength = sideLength;

	mesh.setData(Vertices, Indices);
}
