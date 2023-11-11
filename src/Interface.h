#ifndef INTERFACE_CLASS_H
#define INTERFACE_CLASS_H

#include "PhysicsSimulation.h"
#include "UserInterface.h"
#include "Renderer.h"

class Interface
{
public:
	Interface();
	void Run();
	void Close();


private:
	PhysicsSimulation physicsSimulation;

	Renderer renderer;

	UserInterface userInterface;

	void addRigidBody(RigidType type, glm::vec3 position, glm::vec3 color);
};

#endif // !INTERFACE_CLASS_H
