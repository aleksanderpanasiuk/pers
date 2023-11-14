#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "GraphicsComponent.h"
#include "RigidBody.h"

class Object
{
public:
	GraphicsComponent graphicsComponent;
	RigidBody rigidBody;

	void Update();
	void Render(Shader& shader, Camera& camera);
};

#endif // !OBJECT_CLASS_H
