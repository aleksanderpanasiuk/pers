#ifndef PLANE_CLASS_H
#define PLANE_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "GeometryUtils.h"

class Plane
{
public:
	Plane(glm::vec3 normalVector, glm::vec3 point);

	glm::vec3 getNormal();
	glm::vec3 getPoint();

	void setPoint(glm::vec3 newPoint);

	void Move(glm::vec3 PositionChange);
	void Scale(glm::vec3 scale);
	void ChangePosition(glm::vec3 newPosition);
	void Rotate(glm::vec3 rotationPoint, glm::vec3 Rotation);

	bool operator||(const Plane& planeB);

private:
	glm::vec3 NormalVector;
	glm::vec3 Point;
};

#endif // !PLANE_CLASS_H
