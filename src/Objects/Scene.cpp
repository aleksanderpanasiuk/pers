#include "Scene.h"

void Scene::addObject(Object object)
{
	Objects.push_back(object);
}

std::vector<Object>& Scene::getObjects()
{
	return Objects;
}

unsigned int Scene::getNumberOfObjects()
{
	return Objects.size();
}

Object& Scene::getObjectByID(unsigned int ID)
{
	for (Object& object : Objects)
	{
		if (object.getID() == ID)
		{
			return object;
		}
	}

	throw std::invalid_argument("Object with given ID does not exist");
}
