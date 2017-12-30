#include "GL_include.h"

#include "Application.h"
#include "Window.h"
#include "InputManager.h"
#include "RendererCP.h"
#include "Scene.h"
#include "Logging.h"

namespace The5 {

	InputManager::InputManager(Application* application, Window* window) : mApplication(application), mWindow(window)
	{
		context = InputContext::disabled;
	}

	void InputManager::changeContext(InputContext newContext)
	{
		InputContext oldContext = context;
		context = newContext;
		LOG("Window \"" << getWindow()->title << "\" context changed: " << oldContext <<"->"  << context);
	}

	void InputManager::handleKeyboardInput(int key, int scancode, int action, int mods)
	{
		//LOG("Window \"" << getWindow()->title << "\" context: " << context << " key:" << key << " action: " << action);

		processInputUniversal(key, scancode, action, mods);

		switch (context)
		{
			case InputContext::disabled:
			{
				LOG("Window \"" << getWindow()->title << "\" has its input disabled!");
				return;
			}
			case InputContext::mainMenu:
			{
				processInputMainMenu(key, scancode, action, mods);
				return;
			}
			case InputContext::inGame:
			{
				processInputInGame(key, scancode, action, mods);
				return;
			}
		}
	}

	Application* InputManager::getApplication()
	{
		return mApplication;
	}

	Window* InputManager::getWindow()
	{
		return mWindow;
	}


	//private:

	void InputManager::processInputMainMenu(int key, int scancode, int action, int mods)
	{
		//LOG("Main Menu key ["<< key << "] pressed.");

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			mApplication->terminate();
			return;
		}
		else if (key != GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			changeContext(InputContext::inGame);
			return;
		}
	}

	void InputManager::processInputInGame(int key, int scancode, int action, int mods)
	{
		//LOG("In Game key [" << key << "] pressed.");

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			changeContext(InputContext::mainMenu);
			return;
		}
	}

	void InputManager::processInputUniversal(int key, int scancode, int action, int mods)
	{
		
		if (key == GLFW_KEY_R && action == GLFW_PRESS)
		{
			/// R =  reload all shaders
			LOG("[R] reload all shaders");
			IComponentProcessor* renderer = mApplication->getComponentProcessor(ComponentProcessorType::RendererType);
			if (renderer != nullptr)
			{
				((RendererCP*)renderer)->setFlagRecompileAllShaders();
			}
		}
		
		if (key == GLFW_KEY_M && action == GLFW_PRESS)
		{
			/// M = print Scene Tree
			LOG("[M] print Scene Tree");
			LOG(mApplication->getScene()->getInfo(true));
		}


	}


	bool InputManager::checkApplicationExists()
	{
		if (this->mApplication == nullptr)
		{
			ERR("InputManager's Application is NULL!");
			return false;
		}
		else return true;
	}

	bool InputManager::checkWindowExists()
	{
		if (this == nullptr)
		{
			ERR("InputManager's Window is NULL!");
			return false;
		}
		else return true;
	}


}
