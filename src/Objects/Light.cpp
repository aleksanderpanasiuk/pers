#include "Light.h"

Light::Light(Shader& shader, glm::vec3 Position) :
	Cube(shader, Position, 0.1f)
{

}

glm::vec4 Light::getColor()
{
	return Light::Color;
}

glm::mat4 Light::getModel()
{
	return Light::Model;
}
