#include "GLWindow.h"

GLWindow::GLWindow(uint32_t width, uint32_t height, const std::string& title)
{
	this->handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if(!this->handle)
	{
		//todo throw something
	}
	glfwMakeContextCurrent(handle);

	static bool gladInit = false;
	if(!gladInit)
	{
		gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		gladInit = true;
	}
}

GLWindow::~GLWindow()
{
	glfwDestroyWindow(this->handle);
}

GLFWwindow* GLWindow::getGLFWHandle() const
{
	return this->handle;
}

uint32_t GLWindow::getWidth() const
{
	int width;
	glfwGetWindowSize(this->handle, &width, nullptr);
	return width;
}

uint32_t GLWindow::getHeight() const
{
	int height;
	glfwGetWindowSize(this->handle, nullptr, &height);
	return height;
}



