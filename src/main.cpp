#include "PhysicsSimulation.h"
#include "UserInterface.h"
#include "Renderer.h"
#include "Objects/Camera.h"
#include "Objects/Cube.h"
#include "Objects/Light.h"

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
	
	/*
	std::vector <Texture> textures = 
	{
		Texture("Resources/Textures/grid.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	*/

	/*	EXAMPLE TEXTURE USAGE
	// floor setup
	// Vertices coordinates
	Vertex floorVertices[] =
	{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
		Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
	};

	// Indices for vertices order
	GLuint floorIndices[] =
	{
		0, 1, 2,
		0, 2, 3
	};
	std::vector <Vertex> verts(floorVertices, floorVertices + sizeof(floorVertices) / sizeof(Vertex));
	std::vector <GLuint> ind(floorIndices, floorIndices + sizeof(floorIndices) / sizeof(GLuint));

	Shader textureShader("Resources/Shaders/texture.vert", "Resources/Shaders/texture.frag");

	Mesh floor;
	floor.setData(verts, ind);
	floor.setTextures(textures);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	textureShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(textureShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	textureShader.setLight(glm::vec4(lightColor, 1.0f), lightPos);
	*/

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

		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

			// background color
			glClearColor(backgroundColor[0], backgroundColor[1], 
				backgroundColor[2], backgroundColor[3]
			);
			

			for (Cube& Cube : Cubes)
			{
				Cube.Draw(camera);
			}

			light.Draw(camera);

			userInterface.Display(deltaTime, FrameDelta);

			// Swap the back buffer with the front buffer
			glfwSwapBuffers(window);
		}
	}

	userInterface.close();

	// textureShader.Delete();
	renderer.Close();

	return 0;
}
