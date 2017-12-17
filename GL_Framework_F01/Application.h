#pragma once

#include "stl_include.h"
#include "GL_include.h"

namespace The5 {

	//using unique_ptr with GLFWwindow needs the explicit destructor
	//--------------------------------------------------------------
	/*
	struct DestroyGLFWwindow {
		void operator()(GLFWwindow* ptr){glfwDestroyWindow(ptr);}
	};
	typedef std::unique_ptr<GLFWwindow, DestroyGLFWwindow> GLFWwindowUP;
	*/

	//forward declarations + typedefs
	class Application;
	typedef std::unique_ptr<The5::Application> Application_uptr;

	class Window;
	typedef std::unique_ptr<The5::Window> Window_uptr;

	class InputManager;
	typedef std::unique_ptr<The5::InputManager> InputManager_uptr;

	class Application
	{
	public:
		//ctor
		Application(unsigned int width, unsigned int height, const char* title);
		~Application();

		//member functions
		Window_uptr addWindow(unsigned int width, unsigned int height, const char* title);

		void startGameLoop();
		void terminate();

		//private member accessor functions
		Window* getWindow();

	private:
		//state
		bool gameLoopRunning;

		//owned Objects
		Window_uptr mWindow_uptr;
		std::vector<Window_uptr> mSubWindows;

		void initApplication(unsigned int width, unsigned int height, const char* title);

		//helper functions
		bool checkWindowExists();
	};

}
