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
	// calculate plane and point lying on it
	glm::vec4 planeData = calculatePlane(face);
	std::pair<bool, glm::vec3> PointData = calculatePoint(planeData, cameraPosition, cameraNormal);

	// check if camera is facing the object
	if (not PointData.first)
		return false;

	// check if the point is within side(square)

	return CheckIfPointInSquare(face, PointData.second);
}

glm::vec4 Inspector::calculatePlane(Face face)
{
	glm::vec3 planeNormal = face.getPlane().getNormal();
	glm::vec3 planePoint = face.getPlane().getPoint();

	float A = planeNormal.x;
	float B = planeNormal.y;
	float C = planeNormal.z;
	float D = -(A * planePoint.x + B * planePoint.y + C * planePoint.z);

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

bool Inspector::CheckIfPointInSquare(Face face, glm::vec3 Point)
{
	std::vector<glm::vec3> Vertices = face.getVertices();
	// provided that Vertices[0] and Vertices[1] create opposite side to Vertices[2] and Vertices[3]
	// and Vertices[1] creates side with Vertices[2]
	glm::vec3 S1 = Vertices[0];
	glm::vec3 S2 = Vertices[1];
	glm::vec3 S3 = Vertices[2];

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
	float epsilon = 0.01f;

	return sideLength+epsilon >= vectorsLength;
}
