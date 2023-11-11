#ifndef SHAPE_CLASS_H
#define SHAPE_CLASS_H

#include "../Mesh.h"
#include "RigidBody.h"

class Shape
{
public:
	Shape();
	Shape(RigidType type, glm::vec3 Color);
	void Draw(Shader& shader, Camera& camera, 
		glm::vec3 Position, glm::vec3 Orientation, glm::vec3 Scale
	);

	bool isVisible = true;


private:
	Mesh mesh;
	RigidType type;


	glm::vec3 Color = glm::vec3(0.0f, 0.0f, 0.0f);


	std::vector <glm::vec3> verticesPosition;
	std::vector <Vertex> Vertices;
	std::vector <GLuint> Indices;

	void setDataCube();
};

#endif // !SHAPE_CLASS_H
