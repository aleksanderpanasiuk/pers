#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <toml/toml.hpp>
#include <string>
#include <unordered_map>

#include "Objects/Camera.h"
#include "Objects/Object.h"

class Renderer
{
public:
	bool shouldClose();
	void Init(toml::v3::table config);
	void Close();
	void Draw(std::vector<Object>& Objects);
	void Swap();
	void moveCamera(float deltaTime);
	void setSettings();

	GLFWwindow* getWindow();
	Camera& getCamera();
	Shader& getDefaultShader();

	// screen dimensions
	const unsigned int WIDTH = 1920;
	const unsigned int HEIGHT = 1080;

	const float FPS = 60.0f;


private:
	GLFWwindow* window;
	bool windowClosed = false;

	Camera camera;

	// basic shader
	std::string defaultVertShaderPath = "Resources/Shaders/default.vert";
	std::string defaultFragShaderPath = "Resoudsadrces/Shaders/default.frag";
	Shader defaultShader;

	
	// light
	std::string lighVertShaderPath = "Resources/Shaders/light.vert";
	std::string lighFragShaderPath = "Resources/Shaders/light.frag";
	glm::vec3 lightPosition = glm::vec3(0.0f, 3.0f, 0.0f);
	glm::vec3 lightColor = glm::vec3(0.0f, 0.0f, 0.0f);
	
	Shader lightShader;


	void setConfig(toml::v3::table config);
	void startGLFW();
	void activateShaders();


	// draw functions for different object types
	void drawBackground();
	void drawObjects(std::vector<Object>& Objects);


	glm::vec4 backgroundColor = glm::vec4(0.13f, 0.13f, 0.13f, 1.0f);
};

#endif // !RENDERER_CLASS_H
