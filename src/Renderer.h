#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <string>
#include <unordered_map>

#include "Objects/Camera.h"
#include "Objects/Shape.h"

class Renderer
{
public:
	Renderer();
	bool shouldClose();
	void Close();
	void Draw(std::vector<RigidBody>& rigidBodies);
	void Swap();
	void moveCamera(float deltaTime);

	GLFWwindow* getWindow();
	Camera& getCamera();
	Shader& getDefaultShader();
	void addShape(Shape& shape);

	// screen dimensions
	const unsigned int WIDTH = 1280;
	const unsigned int HEIGHT = 720;

	const float FPS = 60.0f;


private:
	GLFWwindow* window;
	bool windowClosed = false;

	Camera camera;

	// basic shader
	std::string defaultVertShaderPath = "Resources/Shaders/default.vert";
	std::string defaultFragShaderPath = "Resources/Shaders/default.frag";
	Shader defaultShader;

	
	// light
	std::string lighVertShaderPath = "Resources/Shaders/light.vert";
	std::string lighFragShaderPath = "Resources/Shaders/light.frag";
	glm::vec3 lightPosition = glm::vec3(0.0f, 3.0f, 0.0f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	
	Shader lightShader;


	std::vector<Shape> Shapes;


	void startGLFW();
	void activateShaders();


	// draw functions for different object types
	void drawBackground();
	void drawShapes();


	glm::vec4 backgroundColor = glm::vec4(0.13f, 0.13f, 0.13f, 1.0f);
};

#endif // !RENDERER_CLASS_H
