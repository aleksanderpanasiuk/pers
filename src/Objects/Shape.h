#ifndef SHAPE_CLASS_H
#define SHAPE_CLASS_H

#include "../Mesh.h"
#include "RigidBody.h"

class Shape
{
public:
	Shape(RigidType type);
	void Draw(Shader& shader, Camera& camera);
	bool isVisible = true;

private:
	Mesh mesh;


	glm::vec3 Color = glm::vec3(0.0f, 0.0f, 0.0f);
	

	std::vector <glm::vec3> verticesPosition;
	std::vector <Vertex> Vertices;

	std::vector <GLuint> Indices;
};

#endif // !SHAPE_CLASS_H
