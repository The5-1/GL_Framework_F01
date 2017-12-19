#include "Application.h"

#include "Logging.h"

#include "Window.h"
#include "Scene.h"
#include "Renderer.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "Entity.h"


namespace The5 {

	//extern members are declared in headers
	//but must be defined in one cpp file
	//https://stackoverflow.com/questions/10422034/when-to-use-extern-in-c

	//Static object initialization is undefined
	//https://isocpp.org/wiki/faq/ctors#static-init-order

	//static members must be defined and optionally initialized in the namespace!
	//https://stackoverflow.com/questions/16049306/error-lnk2001-unresolved-external-symbol-private-static-class

	Application::Application(unsigned int width = 1024, unsigned int height = 720, std::string title = "GLFW window")
	{
		initApplication(width, height, title);
	}

	void Application::initApplication(unsigned int width, unsigned int height, std::string title)
	{
		mWindow = nullptr;
		gameLoopRunning = false;
		mWindow = addWindow(width, height, title);
	}
	
	Window_uptr Application::addWindow(unsigned int width = 1024, unsigned int height = 720, std::string title = "GLFW window")
	{
		return Window_uptr(new The5::Window(this,width, height, title));
	}

	Window* Application::getWindow()
	{
		return mWindow.get();
	}

	void Application::startGameLoop()
	{
		if (!checkWindowExists()) return;

		gameLoopRunning = true;
		getWindow()->runGameLoop();
	}

	void Application::terminate()
	{
		gameLoopRunning = false;
		getWindow()->terminate();	
	}

	bool Application::checkWindowExists()
	{
		if (getWindow() == nullptr)
		{
			ERR("Application window is NULL! Make sure Application::initWindow() was called!");
			return false;
		}
		else return true;
	}


	Scene* Application::getScene(unsigned int i)
	{
		return mScenes.at(i).get();
	}


	AssetManager* Application::getAssetManager()
	{
		return mAssetManager.get();
	}


	Application::~Application()
	{
		terminate();

		glfwTerminate();
	}

	/*
	bool Application::checkInputManagerExists()
	{
		if (this->inputManager() == nullptr)
		{
			ERR("Application inputManager is NULL! Make sure Application::initInputManager() was called!");
			return false;
		}
		else return true;
	}
	*/
}
