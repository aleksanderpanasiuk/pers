#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "../Mesh.h"

class Object
{
public:
	Object(Shader& shader);

	void Draw(Camera& camera);
	void changeColor(glm::vec3 newColor);

	void changePosition(glm::vec3 newPosition);
	void Move(glm::vec3 positionChange);
	void Rotate(glm::vec3 rotationChange);
	void Rescale(glm::vec3 newScale);

	glm::vec3 getPosition();

	bool isVisible = true;

protected:
	Mesh mesh;
	Shader* shader;

	glm::vec3 Color;

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

#endif // !OBJECT_CLASS_H
