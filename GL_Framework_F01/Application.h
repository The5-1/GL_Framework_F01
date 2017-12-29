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

		ComponentFactory* getComponentFactory();

		IComponentProcessor* getComponentProcessor(ComponentProcessorType type);

	private:
		//state
		bool gameLoopRunning = false;
		void runGameLoop();

		//owned Objects
		std::vector<Window_uptr> mWindows;
		std::vector<Scene_uptr> mScenes;

		void initApplication(unsigned int width, unsigned int height, std::string title);

		//helper functions
		bool checkWindowExists();

		//Managers
		ComponentFactory_uptr mComponentFactory = nullptr;
		void createComponentFactory();

		AssetManager_uptr mAssetManager = nullptr;
		//void createAssetManager();

		//Component Processors
		/** creates all Component Processors */
		void initComponentProcessors();
		/** rund all Component Processors */
		void runComponentProcessors(double deltaTime);
		/** stores owned ComponentProcessors (NO std::set since there can be different processors working on the same components!)*/
		std::map<ComponentProcessorType, IComponentProcessor_uptr> mComponentProcessors;
		/** raw pointer to Rendnerer in mComponentProcessors */
		RendererCP* mRenderer = nullptr;

	};

}
