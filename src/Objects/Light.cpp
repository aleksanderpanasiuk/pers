#include "Light.h"

Light::Light(Shader& shader, glm::vec3 Position, glm::vec3 Color) :
	Cuboid(shader, Position, glm::vec3(0.1f, 0.1f, 0.1f), Color)
{

}

glm::mat4 Light::getModel()
{
	return Light::Model;
}
