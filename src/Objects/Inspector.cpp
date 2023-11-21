#include "Inspector.h"


void Inspector::Update(GLFWwindow* window, std::vector<Object>& objects, Camera camera)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		SelectObject(window, objects, camera);
	}
}

std::string Inspector::getSelectedObjectData(Object& selectedObject)
{
	std::string ObjectData = "Id: ";
	ObjectData += std::to_string(selectedObject.getID()) + "\n";

	ObjectData += "Object type: ";

	switch (selectedObject.getType())
	{
	case RigidCube:
		ObjectData += "Cube\n";
		break;
	default:
		ObjectData += "Unknown\n";
		break;
	}

	ObjectData += "Position: \n";
	ObjectData += "\tx:" + std::to_string(selectedObject.getPosition().x) + "\n";
	ObjectData += "\ty:" + std::to_string(selectedObject.getPosition().y) + "\n";
	ObjectData += "\tz:" + std::to_string(selectedObject.getPosition().z) + "\n";

	return ObjectData;
}

unsigned int Inspector::getSelectedObjectID()
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

	float rotateY = camera.fieldOfView * (mouseY - (height / 2)) / height;
	float rotateX = -camera.fieldOfView * (mouseX - (width / 2)) / height;

	glm::vec3 cursorNormal = glm::rotate(camera.Orientation, glm::radians(rotateY), glm::normalize(glm::cross(-camera.Orientation, glm::vec3(0.0f, 1.0f, 0.0f))));
	cursorNormal = glm::rotate(cursorNormal, glm::radians(rotateX), glm::normalize(glm::cross(-camera.Orientation, glm::vec3(1.0f, 0.0f, 0.0f))));

	return cursorNormal;
}

bool Inspector::CheckHoverCube(Object& Cube, glm::vec3 cameraPosition, glm::vec3 cameraNormal)
{
	std::vector<std::vector<glm::vec3>> Sides = Cube.getSides();

	for (std::vector<glm::vec3> side : Sides)
	{
		bool check = CheckHoverPlane(side, cameraPosition, cameraNormal);
		if (check)
			return true;
	}

	return false;
}

bool Inspector::CheckHoverPlane(std::vector<glm::vec3> Side, glm::vec3 cameraPosition, glm::vec3 cameraNormal)
{
	// calculate plane and point lying on it
	glm::vec4 Plane = calculatePlane(Side);
	std::pair<bool, glm::vec3> PointData = calculatePoint(Plane, cameraPosition, cameraNormal);

	// check if camera is facing the object
	if (not PointData.first)
		return false;

	// check if the point is within side(square)

	return CheckIfPointInSquare(Side, PointData.second);
}

glm::vec4 Inspector::calculatePlane(std::vector<glm::vec3> Side)
{
	glm::vec3 S1 = Side[0];
	glm::vec3 S2 = Side[1];
	glm::vec3 S3 = Side[2];

	float A = (S2.y - S1.y) * (S3.z - S1.z) - (S2.z - S1.z) * (S3.y - S1.y);
	float B = (S2.z - S1.z) * (S3.x - S1.x) - (S2.x - S1.x) * (S3.z - S1.z);
	float C = (S2.x - S1.x) * (S3.y - S1.y) - (S2.y - S1.y) * (S3.x - S1.x);
	float D = -(A * S1.x + B * S1.y + C * S1.z);

	return glm::vec4(A, B, C, D);
}

std::pair<bool, glm::vec3> Inspector::calculatePoint(glm::vec4 Plane, glm::vec3 cameraPosition, glm::vec3 cameraNormal)
{
	float t = (-Plane.x * cameraPosition.x - Plane.y * cameraPosition.y - Plane.z * cameraPosition.z - Plane.w) /
		(Plane.x * cameraNormal.x + Plane.y * cameraNormal.y + Plane.z * cameraNormal.z);

	// check if camera is facing the object

	return std::make_pair(t > 0, glm::vec3(
		cameraPosition[0] + t * cameraNormal[0],
		cameraPosition[1] + t * cameraNormal[1],
		cameraPosition[2] + t * cameraNormal[2]
	));
}

bool Inspector::CheckIfPointInSquare(std::vector<glm::vec3> Side, glm::vec3 Point)
{
	// provided that Side[0] and Side[1] create opposite side to Side[2] and Side[3]
	// and Side[1] creates side with Side[2]
	glm::vec3 S1 = Side[0];
	glm::vec3 S2 = Side[1];
	glm::vec3 S3 = Side[2];

	return CheckIfPointWithinBoundries(Point, S1, S2) and CheckIfPointWithinBoundries(Point, S2, S3);
}

bool Inspector::CheckIfPointWithinBoundries(glm::vec3 Point, glm::vec3 S1, glm::vec3 S2)
{
	// calculate projected point
	glm::vec3 v = S2 - S1;

	float t = v.x * (Point.x - S1.x) + v.y * (Point.y - S1.y) + v.z * (Point.z - S1.z);
	t /= (v.x * v.x) + (v.y * v.y) + (v.z * v.z);

	glm::vec3 ProjectedPoint(
		S1.x + t * v.x,
		S1.y + t * v.y,
		S1.z + t * v.z
	);


	// calculate vector from side vertices to projected point
	glm::vec3 u1(
		ProjectedPoint.x - S1.x,
		ProjectedPoint.y - S1.y,
		ProjectedPoint.z - S1.z
	);

	glm::vec3 u2(
		ProjectedPoint.x - S2.x,
		ProjectedPoint.y - S2.y,
		ProjectedPoint.z - S2.z
	);

	// check if vectors length sum to side length
	float sideLength = glm::length(S2-S1);
	float vectorsLength = glm::length(u1) + glm::length(u2);
	float epsilon = 0.1f;

	return sideLength+epsilon >= vectorsLength;
}
