#include "GeometryUtils.h"

bool Geometry::CheckIfPointWithinBoundries(glm::vec3 Point, glm::vec3 S1, glm::vec3 S2)
{
	// calculate projected point
	glm::vec3 v = S2 - S1;

	float t = v.x * (Point.x - S1.x) + v.y * (Point.y - S1.y) + v.z * (Point.z - S1.z);
	t /= (v.x * v.x) + (v.y * v.y) + (v.z * v.z);

	glm::vec3 ProjectedPoint(
		S1.x + t * v.x,
		S1.y + t * v.y,
		S1.z + t * v.z
	);


	// calculate vector from side vertices to projected point
	glm::vec3 u1(
		ProjectedPoint.x - S1.x,
		ProjectedPoint.y - S1.y,
		ProjectedPoint.z - S1.z
	);

	glm::vec3 u2(
		ProjectedPoint.x - S2.x,
		ProjectedPoint.y - S2.y,
		ProjectedPoint.z - S2.z
	);

	// check if vectors length sum to side length
	float sideLength = glm::length(S2 - S1);
	float vectorsLength = glm::length(u1) + glm::length(u2);

	return sideLength + Geometry::floatError >= vectorsLength;
}

bool Geometry::CheckIfPointInSquare(std::vector<glm::vec3> Vertices, glm::vec3 Point)
{
	if (Vertices.size() != 3 and Vertices.size() != 4)
	{
		throw std::invalid_argument("Must provide 3 or 4 vertices");
	}

	// provided that Vertices[0] and Vertices[1] create opposite side to Vertices[2] and Vertices[3]
	// and Vertices[1] creates side with Vertices[2]
	glm::vec3 S1 = Vertices[0];
	glm::vec3 S2 = Vertices[1];
	glm::vec3 S3 = Vertices[2];

	return Geometry::CheckIfPointWithinBoundries(Point, S1, S2) and Geometry::CheckIfPointWithinBoundries(Point, S2, S3);
}