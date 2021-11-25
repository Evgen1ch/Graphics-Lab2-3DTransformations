#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>


class GLWindow
{
public:
	GLWindow(uint32_t width, uint32_t height, const std::string& title);
	virtual ~GLWindow();

	GLFWwindow* getGLFWHandle() const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
private:
	GLFWwindow* handle;
};

