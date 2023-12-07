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
}
