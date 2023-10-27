#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
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
	void Draw(Shader& shader, Camera& camera, glm::vec3 Position, glm::mat4 Model);
};
#endif