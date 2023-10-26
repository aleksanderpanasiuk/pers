#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "Object.h"

class Cube : Object
{
public:
	void Draw();
	void changePosition(glm::vec3 newPosition);
	void Rotate(glm::vec3 newOrientation);

private:
	Mesh mesh;
};

#endif
