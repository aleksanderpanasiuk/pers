#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

// Structure to standardize the vertices used in the meshes
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};


class VBO
{
public:
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex>& vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif