#pragma once

#include "stl_include.h"
#include "GL_include.h"

class GLFWwindow;

namespace The5
{
	//using unique_ptr with GLFWwindow needs the explicit destructor
	struct DestroyGLFWwindow {
		void operator()(GLFWwindow* ptr) { glfwDestroyWindow(ptr); }
	};
	typedef std::unique_ptr<GLFWwindow, DestroyGLFWwindow> GLFWwindow_uptr;

	///OpenGL GLFW wrapper
	///https://gamedev.stackexchange.com/questions/58541/how-can-i-associate-a-key-callback-with-a-wrapper-class-instance
	class Window {
	public:
		const char* title;
		unsigned int height;
		unsigned int width;

		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		void activate();
		void setTitle(const char* title);
		void resizeViewport(unsigned int width, unsigned int height);

		void runGameLoop();

		void terminate();

	private:

		//global initialization that is done ONCE independent of Window object
		static bool mGLFW_initialized;
		static bool mGLAD_initialized;
		static bool mGL_initialized;
		static void initGLFW();
		static void initGLAD();
		static void initGL();

		//private members
		GLFWwindow_uptr mGLFWwindow_uptr;
		GLFWwindow* getGLFWwindow();
		void initGLFWwindow(unsigned int width, unsigned int height, const char* title);

		//GL Window Callbacks (same for input, quitting, etc...)
		inline static auto windowResize_callback(GLFWwindow *win, int w, int h) -> void
		{
			//get the The5::Window object that is associated with the GLFWwindow
			Window *window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->resizeViewport(w, h);
		}

		inline static auto windowRefresh_callback(GLFWwindow *win) -> void
		{
			//get the The5::Window object that is associated with the GLFWwindow
			Window *window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			//window->RenderScene(void);
		}

		inline static void windowKey_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			//get the window object that is associated with the GLFWwindow
			Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			//window->mInputManager->handleInput(key, scancode, action, mods);
		}
 
	};
	
}