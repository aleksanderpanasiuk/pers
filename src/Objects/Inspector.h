#ifndef INSPECTOR_CLASS_H
#define INSPECTOR_CLASS_H

#include "Object.h"

class Inspector
{
public:
	void Update(std::vector<Object>& objects, Camera camera);
	std::string getSelectedObjectData();

private:
	std::unique_ptr<Object> SelectedObject;

	void CheckHoverCube(Object& Cube);
	glm::vec4 calculatePlane();
	glm::vec3 calculatePoint();
};

#endif // !INSPECTOR_CLASS_H
