#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using std::string;
using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;


class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const string& name, bool value) const;
	void setInt(const string& name, int value) const;
	void setFloat(const string& name, float value) const;

	void setVec2(const string& name, float x, float y) const;
	void setVec2(const string& name, const glm::vec2& value) const;
	void setVec3(const string& name, float x, float y, float z) const;
	void setVec3(const string& name, const glm::vec3& value) const;
	void setVec4(const string& name, float x, float y, float z, float w) const;
	void setVec4(const string& name, const glm::vec4& value) const;

	void setMat2(const string& name, const glm::mat2& value) const;
	void setMat3(const string& name, const glm::mat3& value) const;
	void setMat4(const string& name, const glm::mat4& value) const;

private:
};
#endif

