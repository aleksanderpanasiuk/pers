#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "Rectangle.h"

class Cube : public Rectangle
{
public:
	Cube(Shader& shader, glm::vec3 Position, float sideLength, glm::vec3 Color);
	

protected:
	float sideLength;
};

#endif
