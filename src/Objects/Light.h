#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include "../Mesh.h"

class Light
{
public:
	Light(Shader&shader, glm::vec3 Position);
	void Draw(Camera& camera);

private:
	Mesh mesh;
	Shader* shader;
};

#endif 
