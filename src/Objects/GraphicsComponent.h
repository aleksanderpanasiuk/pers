#ifndef SHAPE_CLASS_H
#define SHAPE_CLASS_H

#include "../Mesh.h"
#include "RigidBody.h"

class GraphicsComponent
{
public:
	GraphicsComponent(RigidType rigidType, glm::vec3 Color);
	void Draw(
		Shader& shader, Camera& camera, 
		glm::vec3 Position,
		glm::vec3 Orientation,
		glm::vec3 Scale
	);

	void ChangeColor(glm::vec3 Color);
	glm::vec3 getColor();

	bool isVisible = true;


private:
	Mesh mesh;


	glm::vec3 Color = glm::vec3(0.0f, 0.0f, 0.0f);

	static std::vector <glm::vec3> CubeVerticesPosition;
	static std::vector <Vertex> CubeVertices;
	static std::vector <GLuint> CubeIndices;

	void setDataCube();
};

#endif // !SHAPE_CLASS_H
