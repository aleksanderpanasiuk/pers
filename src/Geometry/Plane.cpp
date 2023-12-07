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

void Plane::Rotate(glm::vec3 rotationPoint, glm::vec3 Rotation)
{
	glm::vec3 vectorFromBeginning = Point - rotationPoint;

	vectorFromBeginning = glm::rotateX(vectorFromBeginning, Rotation.x);
	vectorFromBeginning = glm::rotateY(vectorFromBeginning, Rotation.y);
	vectorFromBeginning = glm::rotateZ(vectorFromBeginning, Rotation.z);

	Point = rotationPoint + vectorFromBeginning;

	NormalVector = glm::rotateX(NormalVector, Rotation.x);
	NormalVector = glm::rotateY(NormalVector, Rotation.y);
	NormalVector = glm::rotateZ(NormalVector, Rotation.z);
}
