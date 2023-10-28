#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include "../Mesh.h"

class Light
{
public:
	Light(glm::vec3 Position);
	void setShader(Shader& shader);
	void Draw(Camera& camera);
	glm::vec3 getPosition();
	glm::vec4 getColor();
	glm::mat4 getModel();

private:
	Mesh mesh;
	Shader* shader;
	glm::mat4 Model = glm::mat4(1.0f);

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec4 Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	std::vector <Vertex> Vertices =
	{ //     COORDINATES     //
		Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
	};

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
};

#endif 
