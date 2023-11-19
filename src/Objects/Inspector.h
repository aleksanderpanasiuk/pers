#ifndef INSPECTOR_CLASS_H
#define INSPECTOR_CLASS_H

#include "Object.h"

class Inspector
{
public:
	void Update(std::vector<Object>& objects, Camera camera);
	std::string getSelectedObjectData();

private:
	std::unique_ptr<Object> SelectedObject = nullptr;

	bool CheckHoverCube(Object& Cube, glm::vec3 cameraPosition, glm::vec3 cameraNormal);
	bool CheckHoverPlane(std::vector<glm::vec3> Side, glm::vec3 cameraPosition, glm::vec3 cameraNormal);
	glm::vec4 calculatePlane(std::vector<glm::vec3> Side);
	std::pair<bool, glm::vec3> calculatePoint(glm::vec4 Plane, glm::vec3 cameraPosition, glm::vec3 cameraNormal);
	bool CheckIfPointInSquare(std::vector<glm::vec3> Side, glm::vec3 Point);
	bool CheckIfPointWithinBoundries(glm::vec3 Point, glm::vec3 S1, glm::vec3 S2);
};

#endif // !INSPECTOR_CLASS_H
