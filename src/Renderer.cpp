#include "Renderer.h"


Renderer::Renderer()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "PERS", NULL, NULL);

	if (window == NULL)
	{
		throw "Failed to create GLFW window";
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, WIDTH, HEIGHT);

	camera.setDimensions(WIDTH, HEIGHT, glm::vec3(0.0f, 2.0f, 2.0f));

	lightShader.setShader(lighVertShaderPath, lighFragShaderPath);
	lightShader.Activate();

	defaultShader.setShader(defaultVertShaderPath, defaultFragShaderPath);
	defaultShader.Activate();
	defaultShader.setLight(glm::vec4(lightColor, 1.0f), lightPosition);

	glEnable(GL_DEPTH_TEST);
}

bool Renderer::shouldClose()
{
	return windowClosed or glfwWindowShouldClose(window);
}

void Renderer::Events(float deltaTime)
{
	// Handles camera inputs
	camera.Inputs(deltaTime, window);
	camera.updateMatrix(45.0f, 0.1f, 100.0f);

	glfwPollEvents();

	// temporary exit input
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		Close();
	}
}

void Renderer::Close()
{
	windowClosed = true;
	defaultShader.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Renderer::Draw(std::vector<RigidBody>& rigidBodies)
{
	drawBackground();

	for (RigidBody& rigidBody : rigidBodies)
	{
		drawRigidBody(rigidBody);
	}
}

void Renderer::drawBackground()
{
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// background color
	glClearColor(backgroundColor[0], backgroundColor[1],
		backgroundColor[2], backgroundColor[3]
	);
}

void Renderer::drawRigidBody(RigidBody& rigidBody)
{
	Shapes[rigidBody.getID()].Draw(defaultShader, camera,
		rigidBody.getPosition(), rigidBody.getOrientation(), rigidBody.getScale());
}

void Renderer::Swap()
{
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
}

GLFWwindow* Renderer::getWindow()
{
	return window;
}

Camera& Renderer::getCamera()
{
	return camera;
}

Shader& Renderer::getDefaultShader()
{
	return defaultShader;
}

void Renderer::addShape(unsigned int ID, Shape& shape)
{
	Shapes[ID] = shape;
}