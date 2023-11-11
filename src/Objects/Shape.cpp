#include "Shape.h"

Shape::Shape(RigidType type, glm::vec3 Color)
{
	Shape::Color = Color;
	Shape::type = type;

	switch (type)
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

void Shape::Draw(Shader& shader, Camera& camera,
	glm::vec3 Position, glm::vec3 Orientation, glm::vec3 Scale
)
{
	if (isVisible)
	{
		mesh.Draw(shader, camera, Position, Orientation, Scale);
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

	mesh.setData(Vertices, Indices);
}