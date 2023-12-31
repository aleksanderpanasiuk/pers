#ifndef INTERFACE_CLASS_H
#define INTERFACE_CLASS_H


#include "PhysicsSimulation.h"
#include "UserInterface.h"
#include "Renderer.h"
#include "Objects/Scene.h"
#include "Objects/Inspector.h"

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

	Scene scene;

	Inspector inspector;


	void Config(toml::v3::table config);

	void DrawFrame(float& previousTimeFPS, float deltaTime, float currentTimeFPS);
	void handleEvents(float deltaTime);
	
	double lastAddObjectTime = 0.0f;
	double addObjectCooldown = 0.1f;
	unsigned int addObject(RigidType type, glm::vec3 position,
		glm::vec3 orientation, glm::vec3 scale,
		glm::vec3 color, bool isAffectedByForces,
		float mass
	);

	glm::vec3 newObjectPosition();
	glm::vec3 defaultObjectColor = glm::vec3(0.1f, 0.1f, 0.3f);
	unsigned int addObjectToScene();

	glm::vec3 floorColor = glm::vec3(0.6f, 0.6f, 0.6f);
	unsigned int addFloor(glm::vec3 Size = glm::vec3(10.0f, 0.1f, 10.0f));

	void sceneSetup();
};

#endif // !INTERFACE_CLASS_H
