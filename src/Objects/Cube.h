#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include <vector>	

#include "../VBO.h"
#include "../Shader.h"
#include "../Mesh.h"
#include "Light.h"

class Cube
{
public:
	Cube(Shader& shader, glm::vec3 Position, float sideLength);
	
	void Draw(Camera& camera);
	void changePosition(glm::vec3 newPosition);
	void Move(glm::vec3 positionChange);
	void Rotate(glm::vec3 rotationChange);

	bool isVisible = true;
	

private:
	Mesh mesh;
	Shader* shader;

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Orientation = glm::vec3(45.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	
	float sideLength = 1.0f;
	glm::vec3 Color = glm::vec3(0.5f, 0.2f, 0.2f);


	std::vector <glm::vec3> verticesPosition = {
		glm::vec3(-(sideLength / 2),  -(sideLength / 2),   -(sideLength / 2)),
		glm::vec3((sideLength / 2),  -(sideLength / 2),   -(sideLength / 2)),
		glm::vec3((sideLength / 2),   (sideLength / 2),   -(sideLength / 2)),
		glm::vec3(-(sideLength / 2),   (sideLength / 2),   -(sideLength / 2)),
		glm::vec3(-(sideLength / 2),  -(sideLength / 2),   +(sideLength / 2)),
		glm::vec3((sideLength / 2),  -(sideLength / 2),   +(sideLength / 2)),
		glm::vec3((sideLength / 2),   (sideLength / 2),   +(sideLength / 2)),
		glm::vec3(-(sideLength / 2),   (sideLength / 2),   +(sideLength / 2))
	};

	std::vector <Vertex> Vertices =
	{ //     COORDINATES          //   COLORS   //         NORMALS           // TEXTURE COORDINATES
		Vertex{verticesPosition[0],    Color, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)}, // 0 bottom
		Vertex{verticesPosition[1],    Color, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[2],    Color, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[3],    Color, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[4],    Color, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // 4 top
		Vertex{verticesPosition[5],    Color, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[6],    Color, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[7],    Color, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[0],    Color, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // 8 front
		Vertex{verticesPosition[1],    Color, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[4],    Color, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[5],    Color, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[2],    Color, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // 12 back
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

	std::vector <GLuint> Indices =
	{
		0, 1, 2, // bottom
		0, 2, 3,

		4, 5, 6, // top
		4, 6, 7,

		8, 9, 11, // front
		8, 11, 10,

		13, 12, 14, // back
		13, 14, 15,

		16, 17, 19, // left
		16, 18, 19,

		20, 21, 23, // right
		20, 22, 23
	};

	void recalculateVertices();
};

#endif
