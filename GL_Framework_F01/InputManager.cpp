#include "GL_include.h"
#include "Application.h"
#include "InputManager.h"
#include "Logging.h"

namespace The5 {

	InputManager::InputManager(Application* application, GLFWwindow* window) : mApplication(application), mWindow(window)
	{
		context = InputContext::inGame;

		//glfw is a clibrary and can't handle object methods in callbacks
		//https://gamedev.stackexchange.com/questions/58541/how-can-i-associate-a-key-callback-with-a-wrapper-class-instance
		glfwSetWindowUserPointer(this->mWindow, this);
		glfwSetKeyCallback(this->mWindow, glfw_key_callback);
		//glfwSetWindowUserPointer(this->mWindow, this->mWindow);
	}

	void InputManager::changeContext(InputContext newContext)
	{
		context = newContext;
	}

	void InputManager::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//get the input manager that is associated with the GLFWwindow
		InputManager* im = static_cast<InputManager*>(glfwGetWindowUserPointer(window));

		if (im->context == InputContext::mainMenu)
		{
			im->processInputMainMenu(key, scancode, action, mods);
		}			 
		else if (im->context == InputContext::inGame)
		{
			im->processInputInGame(key, scancode, action, mods);
		}
	}
	
	void InputManager::processInputMainMenu(int key, int scancode, int action, int mods)
	{
		LOG("Main Menu key ["<< key << "] pressed.");

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			mApplication->terminate();
			return;
		}
	}

	void InputManager::processInputInGame(int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			LOG("In Game key [" << key << "] pressed.");
			changeContext(InputContext::mainMenu);
			return;
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
