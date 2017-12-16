#include "GL_include.h"
#include "Application.h"
#include "InputManager.h"

namespace The5 {

	InputManager::InputManager(Application* application) : mApplication(application) {}

	void InputManager::processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			//glfwSetWindowShouldClose(window, true);
		}
	}
}
