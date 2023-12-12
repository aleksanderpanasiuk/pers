#include "RigidBody.h"

const float RigidBody::boundingSphereSizeMultiplier = 1.2f;

RigidBody::RigidBody(
	RigidType type,
	glm::vec3 Position,
	glm::vec3 Orientation,
	glm::vec3 Scale,
	bool isAffectedByForces,
	float mass
)
{
	RigidBody::Position = Position;
	RigidBody::Orientation = Orientation;
	RigidBody::Scale = Scale;
	RigidBody::type = type;
	RigidBody::isAffectedByForces = isAffectedByForces;
	RigidBody::Mass = (mass == 0.0f ? Scale.x* Scale.y* Scale.z : mass);

	// apply standard gravity
	applyForce(mass * Constants::Gravity);
}

void RigidBody::Move(float deltaTime)
{
	if (isAffectedByForces)
	{
		Velocity += (NetForce / Mass) * deltaTime;
	}

	Position += (deltaTime * Velocity);
}

void RigidBody::changePosition(glm::vec3 newPosition)
{
	Position = newPosition;
}

void RigidBody::changeOrientation(glm::vec3 newOrientation)
{
	RigidBody::Orientation = newOrientation;
}

void RigidBody::Rotate(float deltaTime, glm::vec3 rotationChange)
{
	Orientation += rotationChange * deltaTime;
}

void RigidBody::Rescale(glm::vec3 newScale)
{
	Scale = newScale;
}

void RigidBody::setVelocity(glm::vec3 Velocity)
{
	RigidBody::Velocity = Velocity;
}

void RigidBody::applyForce(glm::vec3 Force)
{
	NetForce += Force;
}

float RigidBody::getBoundingSphereRadius()
{
	switch (type)
	{
	case RigidCube:
		return getBoundingSphereRadiusCube();
	default:
		return 0.0f;
	}
	return 0.0f;
}

float RigidBody::getBoundingSphereRadiusCube()
{
	float diameter = glm::sqrt(Scale.x * Scale.x + Scale.t * Scale.y + Scale.z * Scale.z);

	return diameter/2 * boundingSphereSizeMultiplier;
}

std::vector<Face> RigidBody::getFaces()
{
	switch (type)
	{
	case RigidCube:
		return getCubeFaces();
	default:
		return std::vector<Face>();
	}
}

std::vector<Face> RigidBody::getCubeFaces()
{
	std::vector<Face> transformedFaces;
	
	for (Face rawFace: CubeFaces)
	{
		rawFace.Scale(Scale);

		rawFace.Rotate(glm::vec3(0.0f, 0.0f, 0.0f), Orientation);
		rawFace.Move(Position);

		transformedFaces.push_back(rawFace);
	}

	return transformedFaces;
}

glm::vec3 RigidBody::getVelocity()
{
	return Velocity;
}

glm::vec3 RigidBody::getPosition()
{
	return Position;
}

glm::vec3 RigidBody::getOrientation()
{
	return Orientation;
}

glm::vec3 RigidBody::getScale()
{
	return Scale;
}

RigidType RigidBody::getType()
{
	return type;
}

float RigidBody::getMass()
{
	return Mass;
}

/*
	   +----------------------------------+
	  / | 7								/ | 6
	 /  			*(0,0.5,0)		   /  |
	/   |			|				  /   |
   /    							 /    |
  +---------------------------------+     |
  |	3	|							| 2   |
  |						*(0,0,0.5)	|	  |
  |		|			 |/				|	  |
  |	 *-(0.5,0,0)	-*- 			| -*(0.5,0,0)
  |		|			/|				|	  |
  |				   *(0,0,-0.5)		|	  |
  |		|							|	  |
  |		+  --  --  --  --  --  --  -| -- +
  |      4  		 |				|	 / 5
  |   /				 *(0,-0.5,0)	|   /
  |  								|  /
  | /								| /
  +---------------------------------+
   0								 1

	y
	^
	|  z
	| /
	|/
	#----- > x
*/

// order of vertices in planes mustn't change
// adjacent vertices create edges

std::vector<Plane> RigidBody::CubePlanes = {
	// x planes
	Plane(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f)), // (1, 2, 6, 5)
	Plane(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(-0.5f, 0.0f, 0.0f)), // (0, 3, 7, 4)

	// y planes
	Plane(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, -0.5f, 0.0f)), // (0, 1, 5, 4)
	Plane(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.5f, 0.0f)), // (2, 3, 7, 6)

	// z planes
	Plane(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -0.5f)), // (0, 1, 2, 3)
	Plane(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.5f)), // (4, 5, 6, 7)
};

std::vector <glm::vec3> RigidBody::CubeVertices = {
		glm::vec3(-0.5f,  -0.5f,   -0.5f),
		glm::vec3( 0.5f,  -0.5f,   -0.5f),
		glm::vec3( 0.5f,   0.5f,   -0.5f),
		glm::vec3(-0.5f,   0.5f,   -0.5f),
		glm::vec3(-0.5f,  -0.5f,    0.5f),
		glm::vec3( 0.5f,  -0.5f,    0.5f),
		glm::vec3( 0.5f,   0.5f,    0.5f),
		glm::vec3(-0.5f,   0.5f,    0.5f)
};

std::vector<Face> RigidBody::CubeFaces = {
	Face(CubePlanes[0], {CubeVertices[1], CubeVertices[2], CubeVertices[6], CubeVertices[5]}),
	Face(CubePlanes[1], {CubeVertices[0], CubeVertices[3], CubeVertices[7], CubeVertices[4]}),
	Face(CubePlanes[2], {CubeVertices[0], CubeVertices[1], CubeVertices[5], CubeVertices[4]}),
	Face(CubePlanes[3], {CubeVertices[2], CubeVertices[3], CubeVertices[7], CubeVertices[6]}),
	Face(CubePlanes[4], {CubeVertices[0], CubeVertices[1], CubeVertices[2], CubeVertices[3]}),
	Face(CubePlanes[5], {CubeVertices[4], CubeVertices[5], CubeVertices[6], CubeVertices[7]}),
};