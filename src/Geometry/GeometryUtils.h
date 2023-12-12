#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <vector>
#include <stdexcept>

#include "Plane.h"
#include "../Utils/Constants.h"

namespace Geometry
{
	bool CheckIfPointWithinBoundries(glm::vec3 Point, glm::vec3 S1, glm::vec3 S2);
	bool CheckIfPointInSquare(std::vector<glm::vec3> Vertices, glm::vec3 Point);

	std::pair<bool, glm::vec3> projectPoint(Plane plane, glm::vec3 point, glm::vec3 projectionVector);
	glm::vec3 projectPoint(Plane plane, glm::vec3 point);
}


#endif // !GEOMETRY_UTILS_H
