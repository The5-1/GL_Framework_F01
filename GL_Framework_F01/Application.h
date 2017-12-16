#pragma once

#include "stl_include.h"
#include "GL_include.h"
#include "InputManager.h"

namespace The5 {
	
	//using unique_ptr with GLFWwindow needs the explicit destructor
	//--------------------------------------------------------------
	struct DestroyGLFWwindow {
		void operator()(GLFWwindow* ptr){glfwDestroyWindow(ptr);}
	};

	class Application;

	typedef std::unique_ptr<GLFWwindow, DestroyGLFWwindow> GLFWwindowUP;
	//typedef std::unique_ptr<The5::Application> ApplicationUP;
	typedef std::unique_ptr<The5::InputManager> inputManagerUP;

	//Static object initialization is undefined
	//https://isocpp.org/wiki/faq/ctors#static-init-order
	class Application
	{
	public:

		//use a namespace-global object instead of singleton or statics? https://www.ics.com/designpatterns/book/namespace-example.html

		//static Application* application();
		static GLFWwindow* window();
		static InputManager* inputManager();

		//static void initApplication();
		static void initWindow(unsigned int width, unsigned int height, const char* title);
		static void initInputManager();	
		static void startGameLoop();
		static void terminate();

	private:

		//static ApplicationUP mApplication;
		static GLFWwindowUP mWindow;
		static inputManagerUP mInputManager;

		Application(); //private constructor since the user shall not create more applications
	};



}
