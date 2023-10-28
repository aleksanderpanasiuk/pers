#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include "Cube.h"

class Light : public Cube
{
public:
	Light(Shader& shader, glm::vec3 Position);

	glm::vec4 getColor();
	glm::mat4 getModel();


private:
	glm::mat4 Model = glm::mat4(1.0f);
	glm::vec4 Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

#endif 
