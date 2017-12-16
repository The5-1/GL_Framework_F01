#pragma once

#include "stl_include.h"
#include "GL_include.h"

namespace The5
{
	///GLFWwindow wrapper
	///https://gamedev.stackexchange.com/questions/58541/how-can-i-associate-a-key-callback-with-a-wrapper-class-instance
	class Window {
	public:
		const char* title;
		Window(unsigned int width, unsigned int height, const char* title);

		auto ViewportDidResize(int w, int h) ->void;
		// Make virtual you want to subclass so that windows have 
		// different contents. Another strategy is to split the
		// rendering calls into a renderer class.
		//auto RenderScene(void) -> void;
		//auto UpdateScene(double ms) ->void;
		// etc for input, quitting

	private:
		GLFWwindow* mGLFWwindow;

		// Here are our callbacks. I like making them inline so they don't take up
		// any of the cpp file
		inline static auto WindowResizeCallback(GLFWwindow *win, int w, int h) -> void
		{
			Window *window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->ViewportDidResize(w, h);
		}

		inline static auto WindowRefreshCallback(GLFWwindow *win) -> void
		{
			Window *window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			//window->RenderScene(void);
		}

		// same for input, quitting, etc
	};
}