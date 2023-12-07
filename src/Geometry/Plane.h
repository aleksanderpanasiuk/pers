#ifndef PLANE_CLASS_H
#define PLANE_CLASS_H

#include <glm/glm.hpp>

class Plane
{
public:
	Plane(glm::vec3 normalVector, glm::vec3 point);

	glm::vec3 getNormal();
	glm::vec3 getPoint();

	void ChangePosition(glm::vec3 newPosition);
	void Rotate(glm::vec3 rotationPoint, glm::vec3 Rotation);

private:
	glm::vec3 NormalVector;
	glm::vec3 Point;
};

#endif // !PLANE_CLASS_H
