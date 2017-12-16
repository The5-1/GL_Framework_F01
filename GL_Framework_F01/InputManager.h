#pragma once

#include "Application.h"
#include "GL_include.h"

namespace The5 {

	class InputManager
	{
	public:
		InputManager(Application* application);

		void processInput(GLFWwindow* window);

	private:
		Application* mApplication;
		
	};

}
