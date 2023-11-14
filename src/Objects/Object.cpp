#include "Object.h"

void Object::Update()
{

}

void Object::Render(Shader& shader, Camera& camera)
{
	graphicsComponent.Draw(shader, camera)
}