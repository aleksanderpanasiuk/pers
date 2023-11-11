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