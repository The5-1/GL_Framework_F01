#pragma once

#include "stl_include.h"
#include "GL_include.h"

#include "ForwardDeclarations.h"

#include "Logging.h"
#include "InputManager.h"


namespace The5
{
	//using unique_ptr with GLFWwindow needs the explicit destructor
	struct DestroyGLFWwindow {
		void operator()(GLFWwindow* ptr) { glfwDestroyWindow(ptr); }
	};
	typedef std::unique_ptr<GLFWwindow, DestroyGLFWwindow> GLFWwindow_uptr;


	///OpenGL GLFW wrapper
	///https://gamedev.stackexchange.com/questions/58541/how-can-i-associate-a-key-callback-with-a-wrapper-class-instance
	class Window {
	public:
		std::string title;
		std::stringstream titlestream;
		unsigned int height;
		unsigned int width;
		unsigned int vSyncIntervall = 1;

		Window(Application* application, unsigned int width, unsigned int height, std::string title);
		~Window();

		void setTitle(std::string title);
		void resizeViewport(unsigned int width, unsigned int height);
		bool checkWindowShouldClose();

		Application* getApplication();
		InputManager* getInputManager();
		double getDeltaFrameTime();
	private:
		friend Application;

		void activate();
		void preUpdate();
		void postUpdate();
		void runGameLoop();
		void terminate();

		double previousFrameTime = 0.0;
		double currentFrameTime = 0.0;
		double deltaFrameTime = 0.0;
		void updateFrameTime();
		void updateWindowTitleInfo();

		//global initialization that is done ONCE independent of Window object
		static bool mGLFW_initialized;
		static bool mGLAD_initialized;
		static bool mGL_initialized;
		static void initGLFW();
		static void initGLAD();
		static void initGL();
		void registerGLFWCallbacks();

		//private members
		Application* mApplication;

		GLFWwindow_uptr mGLFWwindow_uptr;
		GLFWwindow* getGLFWwindow();
		void initGLFWwindow(unsigned int width, unsigned int height, std::string title);

		InputManager_uptr mInputManager_uptr;
		void initInputManager();


		//************** Static Callback Functions ****************//
		//1.) In "Window::registerGLFWCallbacks()" we use the "glfwSetWindowUserPointer()" to link our The5::Window object to the the GLFWwindow object
		//2.) All GLFWwindow object fire the same static callbacks...
		//3.) But we linked exactly one The5::Window to each GLFWwindow
		//4.) So in the callbacks we check what window fired the callback by fetching the The5::Window via "glfwGetWindowUserPointer()"
		//5.) Then we perform the actual methods on the fetched The5::Window
		inline static auto windowResize_callback(GLFWwindow *window, int w, int h) -> void
		{
			Window *win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			win->resizeViewport(w, h);
		}

		inline static auto windowRefresh_callback(GLFWwindow *window) -> void
		{
			Window *win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			//window->RenderScene(void);
		}

		inline static void windowKey_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			//The GLFWwindow handles inputs, so we let our The5::Window do the __initial__ handling too...
			//... so it can be used better with glfwGetWindowUserPointer()
			//We then just call the InputManager associated with the returned The5::Window 
			The5::Window* win = static_cast<The5::Window*>(glfwGetWindowUserPointer(window));
			win->getInputManager()->handleKeyboardInput(key, scancode, action, mods);
		}
 
	};
	
}