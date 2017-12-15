#pragma once


#include "GL_include.h"


namespace The5 {

	class InputManager
	{
	public:


		void processInput(GLFWwindow *window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(window, true);
			}
		}
		
	};

}
