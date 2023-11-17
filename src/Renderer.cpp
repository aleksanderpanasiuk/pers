#include "Renderer.h"


void Renderer::Init(toml::v3::table config)
{
	setConfig(config);


	startGLFW();

	camera.setDimensions(WIDTH, HEIGHT, glm::vec3(0.0f, 2.0f, 2.0f));

	activateShaders();
}

void Renderer::setConfig(toml::v3::table config)
{
	// load shader scripts
	auto shadersData = config["shaders"];

	defaultVertShaderPath = shadersData["defaultVertShaderPath"].value_or("");
	defaultFragShaderPath = shadersData["defaultFragShaderPath"].value_or("");

	lighVertShaderPath = shadersData["lighVertShaderPath"].value_or("");
	lighFragShaderPath = shadersData["lighFragShaderPath"].value_or("");


	// load colors
	auto colorsData = config["colors"];

	auto lColor = colorsData["lightColor"];
	lightColor = glm::vec3(
		lColor[0].value_or(0.0f), 
		lColor[1].value_or(0.0f), 
		lColor[2].value_or(0.0f)
	);

	auto bgColor = colorsData["backgroundColor"];
	backgroundColor = glm::vec4(
		bgColor[0].value_or(0.0f),
		bgColor[1].value_or(0.0f),
		bgColor[2].value_or(0.0f),
		bgColor[3].value_or(0.0f)
	);
}

void Renderer::startGLFW()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "PERS", NULL, NULL);

	if (window == NULL)
	{
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);
}

void Renderer::activateShaders()
{
	lightShader.setShader(lighVertShaderPath, lighFragShaderPath);
	lightShader.Activate();

	defaultShader.setShader(defaultVertShaderPath, defaultFragShaderPath);
	defaultShader.Activate();
	defaultShader.setLight(glm::vec4(lightColor, 1.0f), lightPosition);
}

bool Renderer::shouldClose()
{
	return windowClosed or glfwWindowShouldClose(window);
}

void Renderer::moveCamera(float deltaTime)
{
	// Handles camera inputs
	camera.Inputs(deltaTime, window);
	camera.updateMatrix(45.0f, 0.1f, 1000.0f);
}

void Renderer::Close()
{
	windowClosed = true;
	defaultShader.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Renderer::Draw(std::vector<Object>& Objects)
{
	drawBackground();

	drawObjects(Objects);
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

void Renderer::drawObjects(std::vector<Object>& Objects)
{
	for (Object& object : Objects)
	{
		object.Render(defaultShader, camera);
	}
}

void Renderer::setSettings()
{

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
