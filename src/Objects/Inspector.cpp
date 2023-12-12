#include "Inspector.h"


void Inspector::Update(GLFWwindow* window, std::vector<Object>& objects, Camera camera)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		SelectObject(window, objects, camera);
	}
}

unsigned int &Inspector::getSelectedObjectID()
{
	return SelectedObject;
}

void Inspector::SelectObject(GLFWwindow* window, std::vector<Object>& objects, Camera camera)
{
	glm::vec3 cameraNormal = CalculateCursorVector(window, camera);
	glm::vec3 cameraPosition = camera.Position;
	float closestObjectDistance = 9999999.0f;

	for (Object& object : objects)
	{
		if (isPointingAtObject(object, cameraPosition, cameraNormal))
		{
			float distance = glm::length(cameraPosition - object.getPosition());

			if (distance < closestObjectDistance)
			{
				closestObjectDistance = distance;
				SelectedObject = object.getID();
			}
		}
	}
}

bool Inspector::isPointingAtObject(Object& object, glm::vec3 cameraPosition, glm::vec3 cameraNormal)
{
	bool isPointing = false;

	switch (object.getType())
	{
	case RigidCube:
		isPointing = CheckHoverCube(object, cameraPosition, cameraNormal);
		break;
	default:
		break;
	}

	return isPointing;
}

glm::vec3 Inspector::CalculateCursorVector(GLFWwindow* window, Camera camera)
{
	// Stores the coordinates of the cursor
	double mouseX;
	double mouseY;	
	// Fetches the coordinates of the cursor
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// get window dimensions
	int widthI;
	int heightI;
	glfwGetWindowSize(window, &widthI, &heightI);

	float width = (float)widthI;
	float height = (float)heightI;

	// calculate cursor vector

	glm::vec3 vy = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 vx = glm::vec3(width/height, 0.0f, 0.0f);
	glm::vec3 vc = glm::vec3(0.0f, 0.0f, -1.0f);

	vx = vx * (float)(mouseX - (width/ 2)) / width;
	vy = vy * (float)(mouseY - (height / 2)) / height;

	glm::vec3 v = glm::normalize(vc + 2.0f * (vx + vy));

	// rotate cursor vector

	// project camera vector on XZ plane and calculate angle between tham
	glm::vec3 projectedVector = glm::vec3(camera.Orientation.x, 0.0f, camera.Orientation.z);
	float angle = glm::acos(glm::dot(camera.Orientation, projectedVector) / (glm::length(camera.Orientation)*glm::length(projectedVector)));
	
	// check if camera vector is above or below XZ plane
	float rotationX = angle * (camera.Orientation.y >= 0 ? 1 : -1);

	// calculate y rotation
	glm::vec2 c = glm::vec2(camera.Orientation.x, camera.Orientation.z);
	glm::vec2 d = glm::vec2(1.0f, 0.0f);
	float rotationY = glm::atan(glm::dot(c, d), c.x * d.y - c.y * d.x);

	glm::vec3 vr = glm::rotate(v, rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
	vr = glm::rotate(vr, -rotationY, glm::vec3(0.0f, 1.0f, 0.0f));

	return vr;
}

bool Inspector::CheckHoverCube(Object& Cube, glm::vec3 cameraPosition, glm::vec3 cameraNormal)
{
	std::vector<Face> Faces = Cube.getRigidBody().getFaces();

	for (Face face : Faces)
	{
		bool check = CheckHoverFace(face, cameraPosition, cameraNormal);

		if (check)
			return true;
	}

	return false;
}

bool Inspector::CheckHoverFace(Face face, glm::vec3 cameraPosition, glm::vec3 cameraNormal)
{
	// point lying on faces' plane
	std::pair<bool, glm::vec3> PointData = Geometry::projectPoint(face.getPlane(), cameraPosition, cameraNormal);

	// check if camera is facing the object
	if (not PointData.first)
		return false;

	// check if the point is within side(square)

	return Geometry::CheckIfPointInSquare(face.getVertices(), PointData.second);
}
