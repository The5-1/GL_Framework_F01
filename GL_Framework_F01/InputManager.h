#pragma once


#include "GL_include.h"
#include "Application.h"


namespace The5 {

	class InputManager
	{

	public:
		//Application* application;
		//InputManager(Application* application) : application(application) 
		//{}


		void processInput(GLFWwindow *window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				//glfwSetWindowShouldClose(window, true);
			}
		}
		
	};

}
