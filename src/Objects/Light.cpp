#include "Light.h"

Light::Light(Shader& shader, glm::vec3 Position) :
	Object(shader)
{
	Light::Position = Position;

	mesh.setData(Vertices, Indices);
}

glm::vec4 Light::getColor()
{
	return Light::Color;
}

glm::mat4 Light::getModel()
{
	return Light::Model;
}
