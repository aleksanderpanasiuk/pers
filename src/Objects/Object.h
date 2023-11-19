#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "GraphicsComponent.h"
#include "RigidBody.h"

class Object
{
public:
	Object(GraphicsComponent& graphicsComponent, RigidBody& rigidBody);
	void Update(float deltaTime);
	void Render(Shader& shader, Camera& camera);

	GraphicsComponent& getGraphicsComponent();
	RigidBody& getRigidBody();

	RigidType getType();

private:
	GraphicsComponent graphicsComponent;
	RigidBody rigidBody;
	RigidType type;
};

#endif // !OBJECT_CLASS_H
