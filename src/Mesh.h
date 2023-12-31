#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>

#include "VAO.h"
#include "EBO.h"
#include "Objects/Camera.h"
#include "Texture.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO VAO;

	void setData(std::vector <Vertex>& vertices, std::vector <GLuint>& indices);

	void setTextures(std::vector <Texture>& textures);
	void Draw(Shader& shader, Camera& camera,
		glm::vec3 Position, glm::vec3 Orientation, glm::vec3 Scale,
		glm::vec3 Color
	);

private:
	void bindTextures(Shader& shader);
};
#endif