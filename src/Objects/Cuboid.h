#ifndef CUBOID_CLASS_H
#define CUBOID_CLASS_H

#include "Object.h"

class Cuboid : public Object
{
public:
	Cuboid(Shader& shader, glm::vec3 Position, glm::vec3 Size, glm::vec3 Color);

protected:
	glm::vec3 Size;
	glm::vec3 Color;


	std::vector <glm::vec3> verticesPosition;
	std::vector <Vertex> Vertices;

	std::vector <GLuint> Indices =
	{
		0, 1, 2, // front
		0, 2, 3,

		4, 5, 6, // back
		4, 6, 7,

		8, 9, 11, // bottom
		8, 11, 10,

		13, 12, 14, // top
		13, 14, 15,

		16, 17, 19, // left
		16, 18, 19,

		20, 21, 23, // right
		20, 22, 23
	};
};

#endif // !CUBOID_CLASS_H
