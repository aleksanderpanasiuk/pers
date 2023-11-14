#include "Shape.h"

Shape::Shape(std::unique_ptr<RigidBody>& rigidBody, glm::vec3 Color)
	: rigidBodyPtr(std::move(rigidBody))
{
	Shape::Color = Color;

	switch (rigidBodyPtr->getType())
	{
	case RigidCube:
		setDataCube();
		break;
	case RigidSphere:
		break;
	case RigidPlane:
		break;
	default:
		break;
	}
}

void Shape::Draw(Shader& shader, Camera& camera)
{
	if (isVisible)
	{		
		mesh.Draw(shader, camera, 
			rigidBodyPtr->getPosition(),
			rigidBodyPtr->getOrientation(),
			rigidBodyPtr->getScale()
		);
	}
}

void Shape::setDataCube()
{
	glm::vec3 Size = glm::vec3(1.0f, 1.0f, 1.0f);

	/*
		   +----------------------------------+
		  / | 7								/ | 6
		 /  							   /  |
		/   |							  /   |
	   /    							 /    |
	  +---------------------------------+     |
	  |	3	|							| 2   |
	  |									|	  |
	  |		|							|	  |
	  |									|	  |
	  |		|							|	  |
	  |									|	  |
	  |		|							|	  |
	  |		+  --  --  --  --  --  --  -| -- +
	  |      4  						|	 / 5
	  |   /								|   /
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

	verticesPosition = {
		glm::vec3(-(Size.x / 2),  -(Size.y / 2),   -(Size.z / 2)),
		glm::vec3((Size.x / 2),  -(Size.y / 2),   -(Size.z / 2)),
		glm::vec3((Size.x / 2),   (Size.y / 2),   -(Size.z / 2)),
		glm::vec3(-(Size.x / 2),   (Size.y / 2),   -(Size.z / 2)),
		glm::vec3(-(Size.x / 2),  -(Size.y / 2),   +(Size.z / 2)),
		glm::vec3((Size.x / 2),  -(Size.y / 2),   +(Size.z / 2)),
		glm::vec3((Size.x / 2),   (Size.y / 2),   +(Size.z / 2)),
		glm::vec3(-(Size.x / 2),   (Size.y / 2),   +(Size.z / 2))
	};

	Vertices =
	{ //     COORDINATES          //   COLORS   //         NORMALS           // TEXTURE COORDINATES
		Vertex{verticesPosition[0],    Color, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)}, // 0 front
		Vertex{verticesPosition[1],    Color, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[2],    Color, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[3],    Color, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[4],    Color, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // 4 back
		Vertex{verticesPosition[5],    Color, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[6],    Color, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[7],    Color, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[0],    Color, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // 8 bottom
		Vertex{verticesPosition[1],    Color, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[4],    Color, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[5],    Color, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[2],    Color, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // 12 top
		Vertex{verticesPosition[3],    Color, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[6],    Color, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[7],    Color, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[0],    Color, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // 16 left
		Vertex{verticesPosition[3],    Color, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[4],    Color, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[7],    Color, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[1],    Color, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // 20 right
		Vertex{verticesPosition[2],    Color, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[5],    Color, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[6],    Color, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}
	};

	Indices =
	{
		0, 1, 2, // front
		0, 2, 3,

		4, 5, 6, // back
		4, 6, 7,

		8, 9, 11, // bottom
		8, 11, 10,

		13, 12, 14, // top
		13, 14, 15,

		16, 17, 19, // left
		16, 18, 19,

		20, 21, 23, // right
		20, 22, 23
	};

	mesh.setData(Vertices, Indices);
}