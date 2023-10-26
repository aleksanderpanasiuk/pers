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
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	void recalculateVertices();
};

#endif
