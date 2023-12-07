#ifndef FACE_CLASS_H
#define FACE_CLASS_H

#include <vector>

#include "Plane.h"


class Face
{
public:
	Face(Plane plane, std::vector<glm::vec3> Vertices);

	Plane getPlane();

	void Move(glm::vec3 PositionChange);
	void Scale(glm::vec3 scale);
	void ChangePosition(glm::vec3 newPosition);
	void Rotate(glm::vec3 rotationPoint, glm::vec3 Rotation);

private:
	Plane plane;
	std::vector<glm::vec3> Vertices;
};


#endif // !FACE_CLASS_H
