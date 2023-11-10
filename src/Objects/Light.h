#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include "Cuboid.h"

class Light : public Cuboid
{
public:
	Light(Shader& shader, glm::vec3 Position, glm::vec3 Color);

	glm::mat4 getModel();


private:
	glm::mat4 Model = glm::mat4(1.0f);
};

#endif 
