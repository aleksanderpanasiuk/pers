#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(RigidType rigidType, glm::vec3 Color)
{
	GraphicsComponent::Color = Color;

	switch (rigidType)
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

void GraphicsComponent::Draw(
	Shader& shader, Camera& camera,
	glm::vec3 Position,
	glm::vec3 Orientation,
	glm::vec3 Scale
)
{
	if (isVisible)
	{		
		mesh.Draw(shader, camera, 
			Position,
			Orientation,
			Scale,
			Color
		);
	}
}

void GraphicsComponent::ChangeColor(glm::vec3 Color)
{
	GraphicsComponent::Color = Color;
}

void GraphicsComponent::setDataCube()
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
	{ //     COORDINATES          //         NORMALS          
		Vertex{verticesPosition[0], glm::vec3(0.0f, 0.0f, -1.0f)},   // 0 front
		Vertex{verticesPosition[1], glm::vec3(0.0f, 0.0f, -1.0f)},
		Vertex{verticesPosition[2], glm::vec3(0.0f, 0.0f, -1.0f)},
		Vertex{verticesPosition[3], glm::vec3(0.0f, 0.0f, -1.0f)},

		Vertex{verticesPosition[4], glm::vec3(0.0f, 0.0f, 1.0f)},   // 4 back
		Vertex{verticesPosition[5], glm::vec3(0.0f, 0.0f, 1.0f)},
		Vertex{verticesPosition[6], glm::vec3(0.0f, 0.0f, 1.0f)},
		Vertex{verticesPosition[7], glm::vec3(0.0f, 0.0f, 1.0f)},

		Vertex{verticesPosition[0], glm::vec3(0.0f, -1.0f, 0.0f)},   // 8 bottom
		Vertex{verticesPosition[1], glm::vec3(0.0f, -1.0f, 0.0f)},
		Vertex{verticesPosition[4], glm::vec3(0.0f, -1.0f, 0.0f)},
		Vertex{verticesPosition[5], glm::vec3(0.0f, -1.0f, 0.0f)},

		Vertex{verticesPosition[2], glm::vec3(0.0f, 1.0f, 0.0f)},   // 12 top
		Vertex{verticesPosition[3], glm::vec3(0.0f, 1.0f, 0.0f)},
		Vertex{verticesPosition[6], glm::vec3(0.0f, 1.0f, 0.0f)},
		Vertex{verticesPosition[7], glm::vec3(0.0f, 1.0f, 0.0f)},

		Vertex{verticesPosition[0], glm::vec3(-1.0f, 0.0f, 0.0f)},   // 16 left
		Vertex{verticesPosition[3], glm::vec3(-1.0f, 0.0f, 0.0f)},
		Vertex{verticesPosition[4], glm::vec3(-1.0f, 0.0f, 0.0f)},
		Vertex{verticesPosition[7], glm::vec3(-1.0f, 0.0f, 0.0f)},

		Vertex{verticesPosition[1], glm::vec3(1.0f, 0.0f, 0.0f)},   // 20 right
		Vertex{verticesPosition[2], glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{verticesPosition[5], glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{verticesPosition[6], glm::vec3(1.0f, 0.0f, 0.0f)}
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