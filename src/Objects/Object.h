#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "GraphicsComponent.h"
#include "RigidBody.h"

class Object
{
public:
	Object(unsigned int ID, GraphicsComponent& graphicsComponent, RigidBody& rigidBody);
	void Update(float deltaTime);
	void Render(Shader& shader, Camera& camera);

	GraphicsComponent& getGraphicsComponent();
	RigidBody& getRigidBody();
	
	glm::vec3 getPosition();
	RigidType getType();
	std::vector<std::vector<glm::vec3>> getSides();
	unsigned int getID();
	std::string getName();
	void setName(std::string name);

private:
	unsigned int ID;
	std::string Name = "";
	GraphicsComponent graphicsComponent;
	RigidBody rigidBody;
	RigidType type;

	std::vector<std::vector<glm::vec3>> calculateSidesCube();
};

#endif // !OBJECT_CLASS_H
