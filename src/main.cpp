#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Mesh.h"
#include "Objects/Camera.h"
#include "Objects/Cuboid.h"
#include "Objects/Cube.h"
#include "Objects/Light.h"

#include <memory>

const unsigned int width = 1280;
const unsigned int height = 720;

// Vertices coordinates
Vertex floorVertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint floorIndices[] =
{
	0, 1, 2,
	0, 2, 3
};


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "PERS", NULL, NULL);

	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	std::vector <Texture> textures = 
	{
		Texture("Resources/Textures/grid.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	// light init and setup
	Shader lightShader("Resources/Shaders/light.vert", "Resources/Shaders/light.frag");
	lightShader.Activate();
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 3.0f, 0.0f);

	Light light(lightShader, lightPos, lightColor);
	glm::mat4 lightModel = light.getModel();
	

	lightModel = glm::translate(lightModel, lightPos);
	lightShader.setLight(glm::vec4(lightColor, 1.0f), lightPos);

	// light.setShader(lightShader);

	// floor setup
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
	
	glEnable(GL_DEPTH_TEST);

	// rectangles and cubes init and setup
	Shader shaderProgram("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");

	shaderProgram.Activate();
	shaderProgram.setLight(glm::vec4(lightColor, 1.0f), lightPos);
	glm::vec3 cubeColor = glm::vec3(0.5f, 0.2f, 0.2f);

	std::vector <Cube> cubes;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cubes.push_back(Cube(shaderProgram, glm::vec3(2.0f * i, 0.0f, 2.0f * j), 1.0f, cubeColor));
		}
	}

	std::vector <Cuboid> cuboids;
	glm::vec3 rectColor = glm::vec3(0.2f, 0.2f, 0.5f);
	glm::vec3 rectSize = glm::vec3(1.0f, 1.0f, 2.0f);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			cuboids.push_back(Cuboid(shaderProgram, glm::vec3(2.0f * i, 0.0f, -3.0f * j), rectSize, rectColor));
		}
	}

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// delta time
	float previousTime = glfwGetTime();
	float previousTimeFPS = glfwGetTime();
	float FPS = 60;

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		// delta tiem calculations
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(deltaTime, window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		glfwPollEvents();

		// temporary exit input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}


		// Draws different meshes
		// floor.Draw(textureShader, camera, objectPos);

		for (Cube& cube : cubes)
		{
			cube.Move(deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
			cube.Rotate(deltaTime, glm::vec3(0.0f, 0.0f, -50.0f));
		}

		for (Cuboid& cuboid : cuboids)
		{
			cuboid.Move(deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
			cuboid.Rotate(deltaTime, glm::vec3(0.0f, 0.0f, -50.0f));
		}


		// rendering frame
		float currentTimeFPS = glfwGetTime();

		if (currentTimeFPS - previousTimeFPS >= 1 / FPS)
		{
			previousTimeFPS = currentTimeFPS;

			// background color
			glClearColor(0.13f, 0.13f, 0.13f, 1.0f);
			
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			for (Cube& cube : cubes)
			{
				cube.Draw(camera);
			}

			for (Cuboid& cuboid : cuboids)
			{
				cuboid.Draw(camera);
			}

			light.Draw(camera);

			ImGui::Begin("TEST IMGUI WINDOW");
			ImGui::Text(("Delta Time: " + std::to_string(deltaTime)).c_str());
			ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			// Swap the back buffer with the front buffer
			glfwSwapBuffers(window);
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	textureShader.Delete();
	shaderProgram.Delete();
	lightShader.Delete();
	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
