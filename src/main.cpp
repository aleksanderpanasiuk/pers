#include "Mesh.h"
#include "Objects/Cube.h"

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

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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

	std::vector <Cube> cubes;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cubes.push_back(Cube(glm::vec3(0.5f*i, 0.0f, 0.5f*j), 0.5f));
		}
	}


	// floor setup
	std::unique_ptr <Shader> shaderProgram(new Shader("Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));
	std::vector <Vertex> verts(floorVertices, floorVertices + sizeof(floorVertices) / sizeof(Vertex));
	std::vector <GLuint> ind(floorIndices, floorIndices + sizeof(floorIndices) / sizeof(GLuint));

	std::unique_ptr <Shader> textureShader(new Shader("Resources/Shaders/texture.vert", "Resources/Shaders/texture.frag"));

	Mesh floor;
	floor.setData(verts, ind);
	floor.setTextures(textures);

	// Shader for light cube
	std::unique_ptr <Shader> lightShader(new Shader("Resources/Shaders/light.vert", "Resources/Shaders/light.frag"));
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light;
	light.setData(lightVerts, lightInd);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);


	lightShader -> Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader -> ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader -> ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram -> Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram -> ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram -> ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram -> ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	textureShader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(textureShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(textureShader->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(textureShader->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		// background color
		glClearColor(0.13f, 0.13f, 0.13f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		// Draws different meshes
		floor.Draw(textureShader, camera, objectPos);

		for (Cube& cube : cubes)
		{
			cube.Draw(shaderProgram, camera);
			cube.Move(glm::vec3(0.005f, 0.0f, 0.0f));
		}

		light.Draw(lightShader, camera, lightPos);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		glfwPollEvents();

		// temporary exit input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}

	}

	textureShader -> Delete();
	shaderProgram -> Delete();
	lightShader -> Delete();
	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
