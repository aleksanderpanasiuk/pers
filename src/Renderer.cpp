#include "Renderer.h"


Renderer::Renderer()
	: camera(WIDTH, HEIGHT, glm::vec3(0.0f, 2.0f, 2.0f)),
	lightShader(lighVertShaderPath, lighFragShaderPath)
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

	lightShader.Activate();

	glEnable(GL_DEPTH_TEST);
}

bool Renderer::shouldRun()
{
	return glfwWindowShouldClose(window);
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
	for (Shader& shader : shaders)
	{
		shader.Delete();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* Renderer::getWindow()
{
	return window;
}

void Renderer::addShader(Shader& shader)
{
	shaders.push_back(shader);
}

void Renderer::activateShaders()
{
	for (Shader& shader : shaders)
	{
		shader.Activate();
		shader.setLight(glm::vec4(lightColor, 1.0f), lightPosition);
	}
}