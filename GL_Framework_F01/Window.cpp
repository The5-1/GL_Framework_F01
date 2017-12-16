#include "Window.h"


namespace The5
{

	Window::Window(unsigned int width, unsigned int height, const char* title) : title(title){
		// initialise glfw and m_glfwWindow,
		// create openGL context, initialise any other c++ resources
		glfwInit();
		mGLFWwindow = glfwCreateWindow(width, height, title, NULL, NULL);

		// needed for glfwGetUserPointer to work
		glfwSetWindowUserPointer(mGLFWwindow, this);

		// set our static functions as callbacks
		glfwSetFramebufferSizeCallback(mGLFWwindow, WindowResizeCallback);
		glfwSetWindowRefreshCallback(mGLFWwindow, WindowRefreshCallback);
	}

	// Standard window methods are called for each window
	auto Window::ViewportDidResize(int w, int h) -> void
	{
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	}
}

