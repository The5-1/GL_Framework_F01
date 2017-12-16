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

		gameLoopRunning = false;
	}
	
	void Application::initWindow(unsigned int width = 1024, unsigned int height = 720, const char* title = "GLFW window")
	{
		mWindow = GLFWwindowUP(The5::GL::initGL(width, height, title));
	}

	void Application::initInputManager()
	{
		if (!checkWindowExists()) return;
		mInputManager = inputManagerUP(new InputManager(this,this->window()));
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
		if (!checkWindowExists()) return;
		if (!checkInputManagerExists()) return;

		gameLoopRunning = true;

		gameLoop();

	}

	void Application::gameLoop()
	{
		while (!glfwWindowShouldClose(this->window()) && gameLoopRunning == true)
		{
			glfwSwapBuffers(this->window());

			//Event processing must be done regularly while you have any windows and is normally done each frame after buffer swapping.
			//http://www.glfw.org/docs/latest/input_guide.html#events
			glfwPollEvents();
		}
	}

	void Application::terminate()
	{
		gameLoopRunning = false;

		glfwSetWindowShouldClose(this->window(), true);

		glfwTerminate();
	}

	bool Application::checkWindowExists()
	{
		if (this->window() == nullptr)
		{
			ERR("Application window is NULL! Make sure Application::initWindow() was called!");
			return false;
		}
		else return true;
	}

	bool Application::checkInputManagerExists()
	{
		if (this->inputManager() == nullptr)
		{
			ERR("Application inputManager is NULL! Make sure Application::initInputManager() was called!");
			return false;
		}
		else return true;
	}


	Application::~Application()
	{
		terminate();
	}
}
