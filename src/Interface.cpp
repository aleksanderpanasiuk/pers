#include "Interface.h"

Interface::Interface()
{
	userInterface.init(renderer.getWindow());
	userInterface.addWindow("test", "test");

	glm::vec3 cubeColor = glm::vec3(0.2f, 0.2f, 0.5f);
	unsigned int rigidBodyID = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			physicsSimulation.addRigidBody(RigidBody(rigidBodyID, RigidCube, glm::vec3(2.0f * i, 0.0f, -3.0f * j)));
			Shape shape(RigidCube, cubeColor);
			renderer.addShape(rigidBodyID, shape);
			rigidBodyID++;
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


		renderer.Events(deltaTime);

		if (renderer.shouldClose())
		{
			break;
		}


		// rendering frame
		float currentTimeFPS = glfwGetTime();

		if (currentTimeFPS - previousTimeFPS >= 1 / renderer.FPS)
		{
			double FrameDelta = currentTimeFPS - previousTimeFPS;
			previousTimeFPS = currentTimeFPS;

			renderer.Draw(physicsSimulation.getRigidBodies());
			userInterface.Display(deltaTime, FrameDelta);

			renderer.Swap();
		}
	}
}

void Interface::Close()
{
	userInterface.close();
	renderer.Close();
}