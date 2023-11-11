#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <string>

#include "Mesh.h"
#include "Shader.h"
#include "Objects/Light.h"

class Renderer
{
public:
	Renderer();
	void Close();
	void Draw();
	void Events();
	GLFWwindow* getWindow();
	void getCamera();

	void addShader(Shader& shader);
	void activateShaders();


private:
	GLFWwindow* window;

	Camera camera;

	std::vector<Shader> shaders;

	
	// light
	std::string lighVertShaderPath = "Resources/Shaders/light.vert";
	std::string lighFragShaderPath = "Resources/Shaders/light.frag";
	glm::vec3 lightPosition = glm::vec3(0.0f, 3.0f, 0.0f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	
	Shader lightShader;


	// screen dimensions
	const unsigned int WIDTH = 1280;
	const unsigned int HEIGHT = 720;

	const float FPS = 60.0f;

	glm::vec4 backgroundColor = glm::vec4(0.13f, 0.13f, 0.13f, 1.0f);
};

#endif // !RENDERER_CLASS_H
