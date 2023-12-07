#include "Face.h"

Face::Face(Plane plane, std::vector<glm::vec3> Vertices)
	: plane(plane)
{
	Face::Vertices = Vertices;
}

void Face::Move(glm::vec3 PositionChange)
{
	plane.Move(PositionChange);

	for (glm::vec3& vertex : Vertices)
	{
		vertex += PositionChange;
	}
}

void Face::Scale(glm::vec3 scale)
{
	plane.Scale(scale);

	for (glm::vec3& vertex : Vertices)
	{
		vertex.x *= scale.x;
		vertex.y *= scale.y;
		vertex.z *= scale.z;
	}
}

void Face::ChangePosition(glm::vec3 newPosition)
{
	glm::vec3 positionChangeVector = newPosition - plane.getPoint();
	plane.Move(positionChangeVector);

	for (glm::vec3& vertex : Vertices)
	{
		vertex += positionChangeVector;
	}
}

void Face::Rotate(glm::vec3 rotationPoint, glm::vec3 Rotation)
{
	plane.Rotate(rotationPoint, Rotation);

	for (glm::vec3& vertex : Vertices)
	{
		glm::vec3 vectorFromBeginning = vertex - rotationPoint;

		vectorFromBeginning = glm::rotateX(vectorFromBeginning, glm::radians(Rotation.x));
		vectorFromBeginning = glm::rotateY(vectorFromBeginning, glm::radians(Rotation.y));
		vectorFromBeginning = glm::rotateZ(vectorFromBeginning, glm::radians(Rotation.z));

		vertex = rotationPoint + vectorFromBeginning;
	}
}
