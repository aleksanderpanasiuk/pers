#include "Interface.h"

Interface::Interface()
{
	userInterface.init(renderer.getWindow());
	userInterface.addWindow("Diagnostic Data", "test");

	// floor
	glm::vec3 floorColor = glm::vec3(0.6f, 0.6f, 0.6f);
	addRigidBody(
		RigidCube, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(10.0f, 0.1f, 10.0f), floorColor, false
	);

	// moving cubes
	glm::vec3 ColorBlue = glm::vec3(0.1f, 0.1f, 0.3f);
	glm::vec3 ColorRed = glm::vec3(0.3f, 0.1f, 0.1f);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			if ((i + j) % 2 == 0)
			{
				addRigidBody(RigidCube, glm::vec3(2.0f * i, 0.0f, -3.0f * j),
					glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
					ColorRed, true);
			}
			else
			{
				addRigidBody(RigidCube, glm::vec3(2.0f * i, 0.0f, -3.0f * j),
					glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 2.0f),
					ColorBlue, true);
			}
		}
	}
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

		physicsSimulation.simulate(deltaTime);

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

	renderer.Draw(physicsSimulation.getRigidBodies());
	userInterface.Display(deltaTime, FrameDelta);

	renderer.Swap();
}

unsigned int Interface::addRigidBody(RigidType type, glm::vec3 position, 
	glm::vec3 orientation, glm::vec3 scale, glm::vec3 color,
	bool isAffectedByForces)
{
	unsigned int nextID = physicsSimulation.getRigidBodiesNumber();

	physicsSimulation.addRigidBody(
		RigidBody(
			nextID, type, position, orientation, scale, isAffectedByForces
		)
	);
	Shape shape(type, color);
	renderer.addShape(nextID, shape);

	return nextID;
}

void Interface::Close()
{
	userInterface.close();
	renderer.Close();
}