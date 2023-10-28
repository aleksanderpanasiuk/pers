#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "Object.h"

class Cube : public Object
{
public:
	Cube(Shader& shader, glm::vec3 Position, float sideLength);
	

protected:
	float sideLength;
	glm::vec3 Color = glm::vec3(0.5f, 0.2f, 0.2f);


	std::vector <glm::vec3> verticesPosition;
	std::vector <Vertex> Vertices;

	std::vector <GLuint> Indices =
	{
		0, 1, 2, // bottom
		0, 2, 3,

		4, 5, 6, // top
		4, 6, 7,

		8, 9, 11, // front
		8, 11, 10,

		13, 12, 14, // back
		13, 14, 15,

		16, 17, 19, // left
		16, 18, 19,

		20, 21, 23, // right
		20, 22, 23
	};
};

#endif
