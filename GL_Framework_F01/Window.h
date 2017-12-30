#pragma once

#include "stl_include.h"
#include "GL_include.h"

#include "ForwardDeclarations.h"

#include "Logging.h"
#include "InputManager.h"


namespace The5
{
	/** using std::unique_ptr with GLFWwindow needs the explicit destructor */
	struct DestroyGLFWwindow 
	{
		void operator()(GLFWwindow* ptr) { glfwDestroyWindow(ptr); }
	};
	typedef std::unique_ptr<GLFWwindow, DestroyGLFWwindow> GLFWwindow_uptr;
	
	///OpenGL GLFW wrapper
	class Window {
	public:
		std::string title;
		std::stringstream titlestream;
		unsigned int height;
		unsigned int width;

		/** vsync 0 = off, 1 = on,  2 = 30FPS */
		unsigned int vSyncIntervall = 1;

		Window(Application* application, unsigned int width, unsigned int height, std::string title);
		~Window();

		void setTitle(std::string title);
		void resizeViewport(unsigned int width, unsigned int height);
		bool checkWindowShouldClose();

		///Getter / Setter
		double getDeltaFrameTime();
		Application* getApplication();
		InputManager* getInputManager();

	private:
		friend Application;
		///Game Loop related
		/** called at the start of the loop */
		void preUpdate();
		/** called before the end of the loop */
		void postUpdate();
		/** called when the window is closed */
		void terminate();

		//void runGameLoop();


		///Frametime related 
		/** last time the frame was checked */
		double previousFrameTime = 0.0;
		/** the time now */
		double currentFrameTime = 0.0;
		/** difference between the last and this check */
		double deltaFrameTime = 0.0;
		/** update the delta time */
		void updateFrameTime();

		/** Set combination of name, FPS, etc. in the windows title */
		void updateWindowTitleInfo();

		///global OpenGL-related initialization. Is done ONCE independent of Window object
		/** set once, if glfwInit() was called */
		static bool mGLFW_initialized;
		/** set once, if gladLoadGLLoader() was called */
		static bool mGLAD_initialized;
		/** set once, if all OpenGL specific things such as DebugCallback were set*/
		static bool mGL_initialized;
		
		///Order of functions required to initialize a working OpenGL window
		/** 1.) Calls glfwInit() and adds the error callback sets GLFW window hints (must be done before createWindow)  */
		static void initGLFW();
		/** 2.) Sets the glfwWindowHint() before a GLFWwindow object is created */
		static void setGLFWhints();
		/** 3.) Creates a GLFWwindow object, providing a context for OpenGL (Context = textures, vertex and element buffers, etc.) */
		void createGLFWwindow(unsigned int width, unsigned int height, std::string title, GLFWwindow* sharedContext = NULL);
		/** 4.) Sets this Windows input mode and inits the InputManager. Requires a GLFWwindow object! */
		void initWindowInput();
		/** 5.) Sets this Windows callbacks for resize, key-input and refresh, providing the GLFWwindow object as user pointer. Requires a GLFWwindow object! */
		void registerWindowCallbacks();
		/** 6.) Sets this Window as active context for OpenGL*/
		void makeWindowActiveContext();
		/** 7.) Calls gladLoadGLLoader(). Needs an active openGL context! */
		static void initGLAD();
		/** 8.) sets up custom OpenGL callbacks, e.g. glEnable(GL_DEBUG_OUTPUT) etc.*/
		static void initGL();

		///private Members
		Application* mApplication;
		GLFWwindow_uptr mGLFWwindow_uptr;
		GLFWwindow* getGLFWwindow();
		InputManager_uptr mInputManager_uptr;
		void initInputManager();


		//************** Static Callback Functions ****************//
		//https://gamedev.stackexchange.com/questions/58541/how-can-i-associate-a-key-callback-with-a-wrapper-class-instance
		//1.) In "Window::registerWindowCallbacks()" we use the "glfwSetWindowUserPointer()" to link our The5::Window object to the the GLFWwindow object
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