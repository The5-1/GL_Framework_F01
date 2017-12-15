#pragma once

#include "stl_include.h"
#include "GL_include.h"
#include "GL_init.h"
#include "Logging.h"
#include "InputManager.h"

namespace The5 {

	struct DestroyglfwWin {

		void operator()(GLFWwindow* ptr) {
			glfwDestroyWindow(ptr);
		}

	};

	typedef std::unique_ptr<GLFWwindow, DestroyglfwWin> GLFWwindowUP;

	typedef std::unique_ptr<InputManager> inputManagerUP;

	class Application
	{
	public:

		GLFWwindowUP window;
		
		inputManagerUP inputManager;

		Application()
		{ 
			inputManager = inputManagerUP(new InputManager());
		}

		GLFWwindow* makeWindow(unsigned int width = 1024, unsigned int height = 720, const char* title = "GLFW window")
		{
			window = GLFWwindowUP(The5::GL::initGL(width,height,title));
			return window.get();
		}
		
		void startGameLoop()
		{
			if (window == nullptr)
			{
				ERR("Application can't start GameLoop because window is NULL!");
				return;
			}

			while (!glfwWindowShouldClose(window.get()))
			{
				inputManager->processInput(window.get());

				glfwSwapBuffers(window.get());
				glfwPollEvents();
			}
		}


		void terminate()
		{
			glfwTerminate();
		}

	};



}
