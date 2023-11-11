#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(std::string filename);

class Shader
{
public:
	GLuint ID;
	void setShader(std::string vertexFile, std::string fragmentFile);

	void Activate();
	void Delete();

	void setLight(glm::vec4 lightColor, glm::vec3 lightPos);

private:
	void compileErrors(unsigned int shader, const char* type);
};


#endif