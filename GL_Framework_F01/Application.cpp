#include "Logging.h"
#include "GL_init.h"

#include "Application.h"

namespace The5 {

	//static members must be defined and optionally initialized in the namespace!
	//https://stackoverflow.com/questions/16049306/error-lnk2001-unresolved-external-symbol-private-static-class
	GLFWwindowUP Application::mWindow = nullptr;
	inputManagerUP Application::mInputManager = nullptr;

	/*
	void Application::initApplication()
	{
		mApplication = ApplicationUP(new Application());
	}
	*/

	void Application::initWindow(unsigned int width = 1024, unsigned int height = 720, const char* title = "GLFW window")
	{
		mWindow = GLFWwindowUP(The5::GL::initGL(width, height, title));
	}

	void Application::initInputManager()
	{
		mInputManager = inputManagerUP(new InputManager());
	}

	/*
	Application* Application::application()
	{
		return mApplication.get();
	}
	*/

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
		if (window == nullptr)
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



	Application::Application()
	{
		/*
		if (application == nullptr)
		{
			application = this;
		}
		else
		{
			ERR("There already is a Application object! Can't create another.");
		}
		*/
	}

}
