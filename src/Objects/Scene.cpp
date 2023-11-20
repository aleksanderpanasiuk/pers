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
