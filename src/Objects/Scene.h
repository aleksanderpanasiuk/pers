#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include "Object.h"

class Scene
{
public:
	void addObject(Object object);
	std::vector<Object>& getObjects();
	unsigned int getNumberOfObjects();
	Object& getObjectByID(unsigned int ID);

private:
	std::vector<Object> Objects;

};

#endif // !SCENE_CLASS_H
