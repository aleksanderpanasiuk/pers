#ifndef INSPECTOR_CLASS_H
#define INSPECTOR_CLASS_H

#include "Object.h"

class Inspector
{
public:
	void Update(std::vector<Object>& objects);
	std::string getSelectedObjectData();

private:
	Object SelectedObject;
	glm::vec4 calculatePlane();
	std::pair<float, float> calculatePoint();
};

#endif // !INSPECTOR_CLASS_H
