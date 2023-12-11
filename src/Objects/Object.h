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
	glm::vec3 getVelocity();
	void setPosition(glm::vec3 Position);
	void setVelocity(glm::vec3 Velocity);

	RigidType getType();
	unsigned int getID();
	std::string getName();
	void setName(std::string name);

	glm::vec3 getColor();
	void changeColor(glm::vec3 Color);

private:
	unsigned int ID;
	std::string Name = "";
	GraphicsComponent graphicsComponent;
	RigidBody rigidBody;
	RigidType type;
};

#endif // !OBJECT_CLASS_H
