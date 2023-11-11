#include "Interface.h"

Interface::Interface()
{
	userInterface.init(renderer.getWindow());
	userInterface.addWindow("test", "test");

	glm::vec3 ColorBlue = glm::vec3(0.1f, 0.1f, 0.3f);
	glm::vec3 ColorRed = glm::vec3(0.3f, 0.1f, 0.1f);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			if ((i+j)%2 == 0)
				addRigidBody(RigidCube, glm::vec3(2.0f * i, 0.0f, -3.0f * j), ColorRed);
			else
				addRigidBody(RigidCube, glm::vec3(2.0f * i, 0.0f, -3.0f * j), ColorBlue);
		}
	}
}

void Interface::Run()
{
	// delta time
	float previousTime = glfwGetTime();
	float previousTimeFPS = glfwGetTime();

	// main loop
	while (!renderer.shouldClose())
	{
		// delta time calculations
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		physicsSimulation.simulate(deltaTime);

		handleEvents(deltaTime);

		if (renderer.shouldClose())
		{
			break;
		}

		// rendering frame
		float currentTimeFPS = glfwGetTime();

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

void Interface::addRigidBody(RigidType type, glm::vec3 position, glm::vec3 color)
{
	unsigned int nextID = physicsSimulation.getRigidBodiesNumber();

	physicsSimulation.addRigidBody(RigidBody(nextID, type, position));
	Shape shape(type, color);
	renderer.addShape(nextID, shape);
}

void Interface::Close()
{
	userInterface.close();
	renderer.Close();
}