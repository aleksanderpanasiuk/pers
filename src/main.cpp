#include "PhysicsSimulation.h"
#include "UserInterface.h"
#include "Renderer.h"
#include "Objects/Cube.h"


int main()
{
	// initialize renderer with default shaders and white light
	Renderer renderer;

	std::vector <Cube> Cubes;
	glm::vec3 rectColor = glm::vec3(0.2f, 0.2f, 0.5f);
	glm::vec3 rectSize = glm::vec3(1.0f, 1.0f, 2.0f);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			Cubes.push_back(Cube(renderer.getDefaultShader(), glm::vec3(2.0f * i, 0.0f, -3.0f * j), rectSize, rectColor));
		}
	}


	// initialize user interface with basic window
	UserInterface userInterface;
	userInterface.init(renderer.getWindow());
	userInterface.addWindow("test", "test");

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

		renderer.Events(deltaTime);

		if (renderer.shouldClose())
		{
			break;
		}

		for (Cube& Cube : Cubes)
		{
			Cube.Move(deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
			Cube.Rotate(deltaTime, glm::vec3(0.0f, 0.0f, -50.0f));
		}


		// rendering frame
		float currentTimeFPS = glfwGetTime();

		if (currentTimeFPS - previousTimeFPS >= 1 / renderer.FPS)
		{
			double FrameDelta = currentTimeFPS - previousTimeFPS;
			previousTimeFPS = currentTimeFPS;

			renderer.Draw();

			for (Cube& Cube : Cubes)
			{
				Cube.Draw(renderer.getCamera());
			}

			userInterface.Display(deltaTime, FrameDelta);

			renderer.Swap();
		}
	}

	userInterface.close();
	renderer.Close();

	return 0;
}
