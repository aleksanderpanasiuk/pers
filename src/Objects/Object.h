#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include <glm/glm.hpp>
#include "../Mesh.h"

class Object
{
public:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 0.0f);

};

#endif
