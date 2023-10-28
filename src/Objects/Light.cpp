#include "Light.h"

Light::Light(glm::vec3 Position)
{
	Light::Position = Position;

	mesh.setData(Vertices, Indices);
}

void Light::setShader(Shader& shader)
{
	Light::shader = &shader;
}

void Light::Draw(Camera& camera)
{
	if (isVisible)
	{
		mesh.Draw(*shader, camera, Position, Orientation, Scale);
	}
}

glm::vec3 Light::getPosition()
{
	return Light::Position;
}


glm::vec4 Light::getColor()
{
	return Light::Color;
}

glm::mat4 Light::getModel()
{
	return Light::Model;
}
