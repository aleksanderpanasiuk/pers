#include "Interface.h"

Interface::Interface()
{
	toml::v3::table config = toml::parse_file("Config/config.toml");
	Config(config);
	renderer.Init(config);

	userInterface.init(renderer.getWindow());

	sceneSetup();
}

void Interface::Config(toml::v3::table config)
{
	// colors
	auto colorsData = config["colors"];

	auto fColor = colorsData["floorColor"];
	floorColor = glm::vec3(
		fColor[0].value_or(0.0f),
		fColor[1].value_or(0.0f),
		fColor[2].value_or(0.0f)
	);
}

void Interface::Run()
{
	float previousTime = (float) glfwGetTime();
	float previousTimeFPS = (float) glfwGetTime();

	// main loop
	while (not renderer.shouldClose())
	{
		// delta time calculations
		float currentTime = (float) glfwGetTime();
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		physicsSimulation.simulate(deltaTime, scene.getObjects());

		handleEvents(deltaTime);

		if (renderer.shouldClose())
		{
			break;
		}

		// rendering frame
		float currentTimeFPS =  (float) glfwGetTime();

		if (currentTimeFPS - previousTimeFPS >= 1 / renderer.FPS)
		{
			DrawFrame(previousTimeFPS, deltaTime, currentTimeFPS);
		}
	}
}

void Interface::handleEvents(float deltaTime)
{
	glfwPollEvents();
	double timeNow = glfwGetTime();

	// exit program on ESC
	if (glfwGetKey(renderer.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		renderer.Close();
	}

	// add object on CTR + LMB
	if (glfwGetMouseButton(renderer.getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS and
		glfwGetKey(renderer.getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS and
		lastAddObjectTime + addObjectCooldown <= timeNow)
	{
		addObjectToScene();
		lastAddObjectTime = timeNow;
	}

	inspector.Update(renderer.getWindow(), scene.getObjects(), renderer.getCamera());
}

void Interface::DrawFrame(float& previousTimeFPS, float deltaTime, float currentTimeFPS)
{
	float FrameDelta = currentTimeFPS - previousTimeFPS;
	previousTimeFPS = currentTimeFPS;

	renderer.moveCamera(FrameDelta);

	renderer.Draw(scene.getObjects());
	userInterface.Display(
		deltaTime, FrameDelta, 
		scene.getObjectByID(inspector.getSelectedObjectID()),
		inspector.getSelectedObjectID(),
		scene.getObjects()
	);

	renderer.Swap();
}

unsigned int Interface::addObject(RigidType type, glm::vec3 position,
	glm::vec3 orientation, glm::vec3 scale, glm::vec3 color,
	bool isAffectedByForces, float mass
)
{
	RigidBody rigidBody(
		type, position, orientation, scale, isAffectedByForces, mass
	);

	GraphicsComponent graphicsComponent(type, color);

	unsigned int ID = scene.getNumberOfObjects();
	scene.addObject(Object(ID, graphicsComponent, rigidBody));

	return ID;
}

glm::vec3 Interface::newObjectPosition()
{
	glm::vec3 CameraPosition = renderer.getCamera().Position;
	glm::vec3 CursorVector = inspector.CalculateCursorVector(
		renderer.getWindow(), renderer.getCamera()
	);

	float distanceFromCamera = 6.0f;

	return CameraPosition + distanceFromCamera*CursorVector;
}

unsigned int Interface::addObjectToScene()
{
	return addObject(
		RigidCube,
		newObjectPosition(),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.1f, 0.1f, 0.3f),
		true,
		1.0f
	);
}

unsigned int Interface::addFloor(glm::vec3 Size)
{
	return addObject(
		RigidCube, 
		glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3(0.0f, 0.0f, 0.0f),
		Size, 
		floorColor, 
		false,
		Size.x * Size.y * Size. z // density = kg/m^3
	);
}

void Interface::Close()
{
	userInterface.close();
	renderer.Close();
}

void Interface::sceneSetup()
{
	// floor
	unsigned int floorID = addFloor(glm::vec3(100.0f, 0.1f, 100.0f));

	scene.getObjectByID(floorID).setName("Floor");

	// moving cubes
	glm::vec3 ColorBlue = glm::vec3(0.1f, 0.1f, 0.3f);
	glm::vec3 ColorRed = glm::vec3(0.3f, 0.1f, 0.1f);


	unsigned int cubeID = addObject(
		RigidCube, 
		glm::vec3(0.0f, 5.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3(1.0f, 1.0f, 1.0f),
		ColorRed, true,
		1.0f
	);
}