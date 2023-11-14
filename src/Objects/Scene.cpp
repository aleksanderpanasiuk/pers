#include "Scene.h"

void Scene::addObject(Object object)
{
	Objects.push_back(object);
}

std::vector<Object>& Scene::getObjects()
{
	return Objects;
}