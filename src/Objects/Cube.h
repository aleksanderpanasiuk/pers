#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "Object.h"
#include "../shaderClass.h"
#include "../Camera.h"

class Cube : Object
{
public:
	Cube(glm::vec3 Position, float sideLength);
	void Draw(std::unique_ptr <Shader>& shader, Camera& camera);
	void changePosition(glm::vec3 newPosition);
	void changeSideLength(float sideLength);
	void Rotate(glm::vec3 newOrientation);

private:
	glm::vec3 Position;
	float sideLength;
	glm::vec3 cubeColor = glm::vec3(0.0f, 1.0f, 0.0f);

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

	void recalculateVertices();
};

#endif
