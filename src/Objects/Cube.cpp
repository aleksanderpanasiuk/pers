#include "Cube.h"

Cube::Cube(glm::vec3 Position, float sideLength)
{
	Cube::Position = Position;
	Cube::sideLength = sideLength;

	recalculateVertices();

	mesh.setData(Vertices, Indices);
}

void Cube::Draw(std::unique_ptr <Shader>& shader, Camera& camera)
{
	recalculateVertices();

	mesh.Draw(shader, camera, Position);
}

void Cube::recalculateVertices()
{
	verticesPosition = {
		glm::vec3(Position[0] - (sideLength / 2), Position[1] - (sideLength / 2), Position[2] - (sideLength / 2)),
		glm::vec3(Position[0] + (sideLength / 2), Position[1] - (sideLength / 2), Position[2] - (sideLength / 2)),
		glm::vec3(Position[0] + (sideLength / 2), Position[1] + (sideLength / 2), Position[2] - (sideLength / 2)),
		glm::vec3(Position[0] - (sideLength / 2), Position[1] + (sideLength / 2), Position[2] - (sideLength / 2)),
		glm::vec3(Position[0] - (sideLength / 2), Position[1] - (sideLength / 2), Position[2] + (sideLength / 2)),
		glm::vec3(Position[0] + (sideLength / 2), Position[1] - (sideLength / 2), Position[2] + (sideLength / 2)),
		glm::vec3(Position[0] + (sideLength / 2), Position[1] + (sideLength / 2), Position[2] + (sideLength / 2)),
		glm::vec3(Position[0] - (sideLength / 2), Position[1] + (sideLength / 2), Position[2] + (sideLength / 2))
	};

	Vertices =
	{ //     COORDINATES          //   COLORS   //         NORMALS           // TEXTURE COORDINATES
		Vertex{verticesPosition[0],    cubeColor, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)}, // 0 bottom
		Vertex{verticesPosition[1],    cubeColor, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[2],    cubeColor, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[3],    cubeColor, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[4],    cubeColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // 4 top
		Vertex{verticesPosition[5],    cubeColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[6],    cubeColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[7],    cubeColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[0],    cubeColor, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // 8 front
		Vertex{verticesPosition[1],    cubeColor, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[4],    cubeColor, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[5],    cubeColor, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[2],    cubeColor, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // 12 back
		Vertex{verticesPosition[3],    cubeColor, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[6],    cubeColor, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[7],    cubeColor, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[0],    cubeColor, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // 16 left
		Vertex{verticesPosition[3],    cubeColor, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[4],    cubeColor, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[7],    cubeColor, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},

		Vertex{verticesPosition[1],    cubeColor, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // 20 right
		Vertex{verticesPosition[2],    cubeColor, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[5],    cubeColor, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{verticesPosition[6],    cubeColor, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}
	};
}

void Cube::Move(glm::vec3 poistionChange)
{
	Position = Position + poistionChange;
}

void Cube::changePosition(glm::vec3 newPoistion)
{
	Position = newPoistion;
}