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

glm::vec4 Plane::getFactors()
{
	return glm::vec4(
		NormalVector.x,
		NormalVector.y,
		NormalVector.z,
		-(NormalVector.x * Point.x + NormalVector.y * Point.y + NormalVector.z * Point.z)
	);
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

bool Plane::operator||(const Plane& planeB)
{
	float k[3] = { 0.0f, 0.0f, 0.0f };

	for (int i = 0; i < 3; i++)
	{
		if (NormalVector[i] == 0 or planeB.NormalVector[i] == 0)
			k[i] = 0.0f;
		else
		{
			k[i] = NormalVector[i] / planeB.NormalVector[i];
		}
	}

	for (int i = 1; i < 3; i++)
	{
		if (not (abs(k[i] - k[i - 1]) < Constants::floatError or
			(abs(k[i]) < Constants::floatError or abs(k[i - 1]) < Constants::floatError)))
			return false;
	}


	return true;
}
