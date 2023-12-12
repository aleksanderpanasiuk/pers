#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <vector>
#include <stdexcept>

namespace Geometry
{
	const float floatError = 0.001f;
	bool CheckIfPointWithinBoundries(glm::vec3 Point, glm::vec3 S1, glm::vec3 S2);
	bool CheckIfPointInSquare(std::vector<glm::vec3> Vertices, glm::vec3 Point);
}


#endif // !GEOMETRY_UTILS_H
