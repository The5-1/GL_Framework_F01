#pragma once

#include "stl_include.h"
#include "GL_include.h"

#include "ForwardDeclarations.h"

namespace The5 {

	class Application
	{
	public:
		//ctor
		Application(unsigned int width, unsigned int height, std::string title);
		~Application();

		//member functions
		Window_uptr addWindow(unsigned int width, unsigned int height, std::string title);

		void startGameLoop();
		void terminate();

		//private member accessor functions
		Window* getWindow();

		Scene* getScene(unsigned int i);

		AssetManager* getAssetManager();

	private:
		//state
		bool gameLoopRunning;

		//owned Objects
		Window_uptr mWindow;
		std::vector<Window_uptr> mSubWindows;

		std::vector<Scene_uptr> mScenes;


		void initApplication(unsigned int width, unsigned int height, std::string title);

		//helper functions
		bool checkWindowExists();

		//Managers
		Renderer_uptr mRenderer = nullptr;
		AssetManager_uptr mAssetManager = nullptr;
	};

}
