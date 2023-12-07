#include "Plane.h"

Plane::Plane(glm::vec3 normalVector, glm::vec3 point)
{
	Plane::NormalVector = normalVector;
	Plane::Point = point;
}

glm::vec3 Plane::getNormal()
{
	return NormalVector;
}

glm::vec3 Plane::getPoint()
{
	return Point;
}

void Plane::ChangePosition(glm::vec3 newPosition)
{
	Plane::Point = newPosition;
}
