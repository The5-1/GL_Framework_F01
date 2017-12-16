#include "Logging.h"
#include "GL_init.h"

#include "Application.h"
#include "InputManager.h"

namespace The5 {

	//extern members are declared in headers
	//but must be defined in one cpp file
	//https://stackoverflow.com/questions/10422034/when-to-use-extern-in-c

	//Static object initialization is undefined
	//https://isocpp.org/wiki/faq/ctors#static-init-order

	//static members must be defined and optionally initialized in the namespace!
	//https://stackoverflow.com/questions/16049306/error-lnk2001-unresolved-external-symbol-private-static-class

	Application::Application()
	{
		initApplication();
	}


	void Application::initApplication()
	{
		mWindow = nullptr;
		mInputManager = nullptr;
	}
	
	void Application::initWindow(unsigned int width = 1024, unsigned int height = 720, const char* title = "GLFW window")
	{
		mWindow = GLFWwindowUP(The5::GL::initGL(width, height, title));
	}

	void Application::initInputManager()
	{
		mInputManager = inputManagerUP(new InputManager(this));
	}

	GLFWwindow* Application::window()
	{
		return mWindow.get();
	}

	InputManager* Application::inputManager()
	{
		return mInputManager.get();
	}

	void Application::startGameLoop()
	{
		if (mWindow.get() == nullptr)
		{
			ERR("Application can't start GameLoop because window is NULL!");
			return;
		}

		while (!glfwWindowShouldClose(mWindow.get()))
		{
			mInputManager->processInput(mWindow.get());

			glfwSwapBuffers(mWindow.get());
			glfwPollEvents();
		}
	}


	void Application::terminate()
	{
		glfwSetWindowShouldClose(mWindow.get(), true);
		glfwTerminate();
	}

}
