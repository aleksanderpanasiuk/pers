#include "Light.h"

Light::Light(Shader& shader, glm::vec3 Position)
{
	Light::shader = &shader;
	Light::Position = Position;

	mesh.setData(Vertices, Indices);
}