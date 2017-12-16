#pragma once

#include "Application.h"
#include "GL_include.h"

namespace The5 {

	enum InputContext { inGame, mainMenu};


	class InputManager
	{
	public:
		InputManager(Application* application, GLFWwindow* window);

		void changeContext(InputContext newContext);

	private:

		//C-Style glfw key callback cant pass a C++ object, hence must be static
		static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		Application* mApplication;
		GLFWwindow* mWindow;

		InputContext context;
	
		void processInputMainMenu(int key, int scancode, int action, int mods);
		void processInputInGame(int key, int scancode, int action, int mods);

		bool checkWindowExists();
		bool checkApplicationExists();
	};

}
