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
	std::vector<glm::vec3> getVertices();

private:
	GraphicsComponent graphicsComponent;
	RigidBody rigidBody;
	RigidType type;


	std::vector<glm::vec3> calculateVerticesCube();
};

#endif // !OBJECT_CLASS_H
