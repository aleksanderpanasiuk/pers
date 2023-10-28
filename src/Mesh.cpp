#include "Mesh.h"

void Mesh::setData(std::vector <Vertex>& vertices, std::vector <GLuint>& indices)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;

	VAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::setTextures(std::vector <Texture>& textures)
{
	Mesh::textures = textures;
}

void Mesh::Draw(Shader& shader, Camera& camera, glm::vec3 Position, glm::vec3 Orientation, glm::vec3 Scale)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO.Bind();	

	if (!textures.empty())
	{
		bindTextures(shader);
	}

	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");


	// creating transofrm model
	// Model = Translate * Rotate * Scale;
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), Position);

	glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f), glm::radians(Orientation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	Rotation = glm::rotate(Rotation, glm::radians(Orientation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	Rotation = glm::rotate(Rotation, glm::radians(Orientation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	Model = glm::scale(Model, Scale) * Rotation;

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(Model));
	// sending rotation twice for normals calculations
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(Rotation));


	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::bindTextures(Shader& shader)
{
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;

		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}

		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
}