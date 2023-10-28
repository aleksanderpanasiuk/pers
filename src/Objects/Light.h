#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include "Cube.h"

class Light : public Cube
{
public:
	Light(Shader& shader, glm::vec3 Position, glm::vec3 Color);

	glm::vec4 getColor();
	glm::mat4 getModel();


private:
	glm::mat4 Model = glm::mat4(1.0f);
};

#endif 
