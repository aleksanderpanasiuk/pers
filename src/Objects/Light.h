#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include "../Mesh.h"

class Light
{
public:
	Light(glm::vec3 POsition);
	void Draw();

private:
	Mesh mesh;
};

#endif 
