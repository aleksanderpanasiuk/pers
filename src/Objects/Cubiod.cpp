#include "Cuboid.h"

Cuboid::Cuboid(Shader& shader, glm::vec3 Position, glm::vec3 Size, glm::vec3 Color) :
	Object(shader)
{
	changeColor(Color);
	changePosition(Position);
	Object::Size = glm::vec3(std::abs(Size.x), std::abs(Size.y), std::abs(Size.z));

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
		glm::vec3( -(Size.x / 2),  -(Size.y / 2),   -(Size.z / 2)),
		glm::vec3(  (Size.x / 2),  -(Size.y / 2),   -(Size.z / 2)),
		glm::vec3(  (Size.x / 2),   (Size.y / 2),   -(Size.z / 2)),
		glm::vec3( -(Size.x / 2),   (Size.y / 2),   -(Size.z / 2)),
		glm::vec3( -(Size.x / 2),  -(Size.y / 2),   +(Size.z / 2)),
		glm::vec3(  (Size.x / 2),  -(Size.y / 2),   +(Size.z / 2)),
		glm::vec3(  (Size.x / 2),   (Size.y / 2),   +(Size.z / 2)),
		glm::vec3( -(Size.x / 2),   (Size.y / 2),   +(Size.z / 2))
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