#include "Interface.h"

Interface::Interface()
{
	userInterface.init(renderer.getWindow());
	userInterface.addWindow("Diagnostic Data", "test");

	// floor
	addFloor();

	// moving cubes
	glm::vec3 ColorBlue = glm::vec3(0.1f, 0.1f, 0.3f);
	glm::vec3 ColorRed = glm::vec3(0.3f, 0.1f, 0.1f);


	addObject(
		RigidCube, glm::vec3(0.0f, 5.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		ColorRed, true
	);
}

void Interface::Run()
{
	float previousTime = (float) glfwGetTime();
	float previousTimeFPS = (float) glfwGetTime();

	// main loop
	while (not renderer.shouldClose())
	{
		// delta time calculations
		float currentTime = (float) glfwGetTime();
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		physicsSimulation.simulate(deltaTime, scene.getObjects());

		handleEvents(deltaTime);

		if (renderer.shouldClose())
		{
			break;
		}

		// rendering frame
		float currentTimeFPS =  (float) glfwGetTime();

		if (currentTimeFPS - previousTimeFPS >= 1 / renderer.FPS)
		{
			DrawFrame(previousTimeFPS, deltaTime, currentTimeFPS);
		}
	}
}

void Interface::handleEvents(float deltaTime)
{
	glfwPollEvents();

	// exit input
	if (glfwGetKey(renderer.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		renderer.Close();
	}

	renderer.moveCamera(deltaTime);
}

void Interface::DrawFrame(float& previousTimeFPS, float deltaTime, float currentTimeFPS)
{
	float FrameDelta = currentTimeFPS - previousTimeFPS;
	previousTimeFPS = currentTimeFPS;

	renderer.Draw(scene.getObjects());
	userInterface.Display(deltaTime, FrameDelta);

	renderer.Swap();
}

void Interface::addObject(RigidType type, glm::vec3 position,
	glm::vec3 orientation, glm::vec3 scale, glm::vec3 color,
	bool isAffectedByForces
)
{
	RigidBody rigidBody(
		type, position, orientation, scale, isAffectedByForces
	);

	GraphicsComponent graphicsComponent(type, color);
	
	scene.addObject(Object(graphicsComponent, rigidBody));
}

void Interface::addFloor(glm::vec3 Size)
{
	addObject(
		RigidCube, 
		glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3(0.0f, 0.0f, 0.0f),
		Size, 
		floorColor, 
		false
	);
}

void Interface::Close()
{
	userInterface.close();
	renderer.Close();
}