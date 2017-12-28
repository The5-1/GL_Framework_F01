#include "Application.h"

#include "Logging.h"

#include "Window.h"
#include "Scene.h"
#include "RendererCP.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "Entity.h"
#include "ComponentManager.h"


namespace The5 {

	//extern members are declared in headers
	//but must be defined in one cpp file
	//https://stackoverflow.com/questions/10422034/when-to-use-extern-in-c

	//Static object initialization is undefined
	//https://isocpp.org/wiki/faq/ctors#static-init-order

	//static members must be defined and optionally initialized in the namespace!
	//https://stackoverflow.com/questions/16049306/error-lnk2001-unresolved-external-symbol-private-static-class

	Application::Application(unsigned int width, unsigned int height, std::string title) : name(title)
	{
		initApplication(width, height, title);
	}

	void Application::initApplication(unsigned int width, unsigned int height, std::string title)
	{
		gameLoopRunning = false;

		addWindow(width, height, title);

		std::string scenetitle = title;
		scenetitle += "_scene";
		addScene(scenetitle);
	}
	
	void Application::createComponentManager()
	{
		this->mComponentManager = ComponentManager_uptr(new ComponentManager(this));
	}


	Window* Application::addWindow(unsigned int width, unsigned int height, std::string title)
	{
		Window* window = new Window(this, width, height, title);
		mWindows.push_back(Window_uptr(window));
		return window;
	}

	Window* Application::getWindow(unsigned int i)
	{
		return mWindows.at(i).get();
	}

	Scene* Application::addScene(std::string name)
	{
		Scene* scene = new Scene(name,this);
		mScenes.push_back(Scene_uptr(scene));
		return scene;
	}

	Scene* Application::getScene(unsigned int i)
	{
		return mScenes.at(i).get();
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

	AssetManager* Application::getAssetManager()
	{
		return mAssetManager.get();
	}

	ComponentManager * Application::getComponentManager()
	{
		return mComponentManager.get();
	}

	Application::~Application()
	{
		terminate();

		glfwTerminate();
	}


}


/*
std::string Application::getInfo()
{
std::string info = "";
info += "Application: " + this->name + "\n";

info += " Scenes:\n";
for (auto& s : mScenes)
{
info += "  " + s.get()->name + "[Scene] \n";
int indent = 3;
info += Entity::getEntityInfo(s->getRoot(), indent);
info += "\n";
}

return info;
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
*/
