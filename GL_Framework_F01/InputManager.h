#pragma once

#include "GL_include.h"

#include "ForwardDeclarations.h"

namespace The5 {


	enum InputContext { disabled, inGame, mainMenu};

	class InputManager
	{
	public:
		InputManager(Application* application, Window* window);

		void changeContext(InputContext newContext);

		void handleKeyboardInput(int key, int scancode, int action, int mods);

		Application* getApplication();
		Window* getWindow();

	private:

		Application* mApplication;
		Window* mWindow;

		InputContext context = InputContext::disabled;
	
		void processInputMainMenu(int key, int scancode, int action, int mods);
		void processInputInGame(int key, int scancode, int action, int mods);
		void processInputUniversal(int key, int scancode, int action, int mods);

		bool checkWindowExists();
		bool checkApplicationExists();
	};

}
