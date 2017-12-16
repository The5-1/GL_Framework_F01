#pragma once

#include "stl_include.h"
#include "GL_include.h"

namespace The5 {

	class Application;
	class InputManager;
	
	//using unique_ptr with GLFWwindow needs the explicit destructor
	//--------------------------------------------------------------
	struct DestroyGLFWwindow {
		void operator()(GLFWwindow* ptr){glfwDestroyWindow(ptr);}
	};


	typedef std::unique_ptr<GLFWwindow, DestroyGLFWwindow> GLFWwindowUP;
	typedef std::unique_ptr<The5::Application> ApplicationUP;
	typedef std::unique_ptr<The5::InputManager> inputManagerUP;

	class Application
	{
	public:

		//private member accessor functions
		GLFWwindow* window();
		InputManager* inputManager();

		//ctor
		Application();

		//member functions
		void initApplication();
		void initWindow(unsigned int width, unsigned int height, const char* title);
		void initInputManager();	
		void startGameLoop();
		void terminate();

	private:
		//private members
		GLFWwindowUP mWindow;
		inputManagerUP mInputManager;
	};

}
