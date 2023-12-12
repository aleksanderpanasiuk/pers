#ifndef INSPECTOR_CLASS_H
#define INSPECTOR_CLASS_H

#include "Object.h"
#include "../Geometry/GeometryUtils.h"

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
};

#endif // !INSPECTOR_CLASS_H
