#ifndef INSPECTOR_CLASS_H
#define INSPECTOR_CLASS_H

#include "Object.h"

class Inspector
{
public:
	void Update(GLFWwindow* window, std::vector<Object>& objects, Camera camera);
	unsigned int &getSelectedObjectID();

	glm::vec3 CalculateCursorVector(GLFWwindow* window, Camera camera);

private:
	unsigned int SelectedObject = 0;

	void SelectObject(GLFWwindow* window, std::vector<Object>& objects, Camera camera);
	bool isPointingAtObject(Object& object, glm::vec3 cameraPosition, glm::vec3 cameraNormal);
	

	bool CheckHoverCube(Object& Cube, glm::vec3 cameraPosition, glm::vec3 cameraNormal);
	bool CheckHoverFace(Face face, glm::vec3 cameraPosition, glm::vec3 cameraNormal);
	glm::vec4 calculatePlane(Face face);
	std::pair<bool, glm::vec3> calculatePoint(glm::vec4 Plane, glm::vec3 cameraPosition, glm::vec3 cameraNormal);
	bool CheckIfPointInSquare(Face face, glm::vec3 Point);
	bool CheckIfPointWithinBoundries(glm::vec3 Point, glm::vec3 S1, glm::vec3 S2);
};

#endif // !INSPECTOR_CLASS_H
