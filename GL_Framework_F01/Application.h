#pragma once

#include "stl_include.h"
#include "GL_include.h"

#include "ForwardDeclarations.h"

namespace The5 {

	class Application
	{
	public:
		//ctor
		Application(unsigned int width = 1024, unsigned int height = 720, std::string title = "Application");
		~Application();

		//member functions

		std::string name;

		void startGameLoop();
		void terminate();

		//private member accessor functions
		Window* getWindow(unsigned int i = 0);
		Window* addWindow(unsigned int width = 1024, unsigned int height = 720, std::string title = "Window");

		Scene* getScene(unsigned int i = 0);
		Scene* addScene(std::string name);

		AssetManager* getAssetManager();

		std::string getInfo();

		ComponentManager* getComponentManager();

	private:
		//state
		bool gameLoopRunning = false;

		//owned Objects
		std::vector<Window_uptr> mWindows;
		std::vector<Scene_uptr> mScenes;

		void initApplication(unsigned int width, unsigned int height, std::string title);

		//helper functions
		bool checkWindowExists();

		//Managers
		ComponentManager_uptr mComponentManager = nullptr;
		void createComponentManager();

		//AssetManager_uptr mAssetManager = nullptr;
		//void createAssetManager();


	};

}
