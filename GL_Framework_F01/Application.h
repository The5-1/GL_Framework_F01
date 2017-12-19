#pragma once

#include "stl_include.h"
#include "GL_include.h"

namespace The5 {

	//using unique_ptr with GLFWwindow needs the explicit destructor
	//--------------------------------------------------------------
	/*
	struct DestroyGLFWwindow {
		void operator()(GLFWwindow* ptr){glfwDestroyWindow(ptr);}
	};
	typedef std::unique_ptr<GLFWwindow, DestroyGLFWwindow> GLFWwindowUP;
	*/

	//forward declarations + typedefs
	class Application;
	typedef std::unique_ptr<The5::Application> Application_uptr;

	class Window;
	typedef std::unique_ptr<The5::Window> Window_uptr;

	class Scene;
	typedef std::unique_ptr<The5::Scene> Scene_uptr;

	class AssetManager;
	typedef std::unique_ptr<AssetManager> AssetManager_uptr;

	class Renderer;
	typedef std::unique_ptr<Renderer> Renderer_uptr;

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
