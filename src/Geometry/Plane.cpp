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

void Plane::setPoint(glm::vec3 newPoint)
{
	Plane::Point = newPoint;
}

void Plane::Move(glm::vec3 PositionChange)
{
	Plane::Point += PositionChange;
}

void Plane::Scale(glm::vec3 scale)
{
	Point.x *= scale.x;
	Point.y *= scale.y;
	Point.z *= scale.z;
}

void Plane::ChangePosition(glm::vec3 newPosition)
{
	Plane::Point = newPosition;
}

void Plane::Rotate(glm::vec3 rotationPoint, glm::vec3 Rotation)
{
	glm::vec3 vectorFromBeginning = Point - rotationPoint;

	vectorFromBeginning = glm::rotateX(vectorFromBeginning, glm::radians(Rotation.x));
	vectorFromBeginning = glm::rotateY(vectorFromBeginning, glm::radians(Rotation.y));
	vectorFromBeginning = glm::rotateZ(vectorFromBeginning, glm::radians(Rotation.z));

	Point = rotationPoint + vectorFromBeginning;

	NormalVector = glm::rotateX(NormalVector, glm::radians(Rotation.x));
	NormalVector = glm::rotateY(NormalVector, glm::radians(Rotation.y));
	NormalVector = glm::rotateZ(NormalVector, glm::radians(Rotation.z));
}
