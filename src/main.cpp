#include "PhysicsSimulation.h"
#include "UserInterface.h"
#include "Renderer.h"
#include "Objects/Cube.h"

#include <memory>

// screen dimensions
const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

const float FPS = 60.0f;

// colors
const glm::vec4 backgroundColor = glm::vec4(0.13f, 0.13f, 0.13f, 1.0f);
const glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);


int main()
{
	Renderer renderer;

	// rectangles and cubes init and setup
	Shader shaderProgram("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");

	renderer.addShader(shaderProgram);
	renderer.activateShaders();

	std::vector <Cube> Cubes;
	glm::vec3 rectColor = glm::vec3(0.2f, 0.2f, 0.5f);
	glm::vec3 rectSize = glm::vec3(1.0f, 1.0f, 2.0f);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			Cubes.push_back(Cube(shaderProgram, glm::vec3(2.0f * i, 0.0f, -3.0f * j), rectSize, rectColor));
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
	while (!renderer.shouldRun())
	{
		// delta tiem calculations
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		renderer.Events(deltaTime);

		if (!renderer.shouldRun())
		{
			break;
		}

		// floor.Draw(textureShader, camera, objectPos);

		for (Cube& Cube : Cubes)
		{
			Cube.Move(deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
			Cube.Rotate(deltaTime, glm::vec3(0.0f, 0.0f, -50.0f));
		}


		// rendering frame
		float currentTimeFPS = glfwGetTime();

		if (currentTimeFPS - previousTimeFPS >= 1 / FPS)
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

	// textureShader.Delete();
	renderer.Close();

	return 0;
}
