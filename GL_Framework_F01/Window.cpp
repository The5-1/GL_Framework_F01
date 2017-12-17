#include "Window.h"
#include "Logging.h"
#include "LoggingGL.h"

namespace The5
{

	//statics need to be defined ONCE 
	//e.g. in the .cpp, not in header since the header is ran multiple times (in each compile-unit) and might define it multiple times!
	bool Window::mGLFW_initialized = false;
	bool Window::mGLAD_initialized = false;
	bool Window::mGL_initialized = false;

	Window::Window(unsigned int width, unsigned int height, const char* title) : width(width), height(height), title(title)
	{
		initGLFW(); //init GLFW and set window hints
		initGLFWwindow(width, height, title); //create the GLFWwindow-object
		activate(); //set the active context for OpenGL to this GLFWwindow and bind callbacks
		initGLAD(); //GLAD needs the active context! GLAD loads OpenGL functions
		initGL(); //init the other stuff that requires active context
	}

//************** OpelGL initialization **************//

	void Window::initGLFW()
	{
		if (!mGLFW_initialized)
		{
			if (glfwInit())
			{
				//glfwWindowHints need to be done before glfwCreateWindow
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

				glfwSetErrorCallback(The5::GL::glfw_error_callback); //set the error callback
				mGLFW_initialized = true;
			}
			else
			{
				ERR("Failed to init GLFW!");
				mGLFW_initialized = false;
				return;
			}

		}
	}

	void Window::initGLFWwindow(unsigned int width = 1024, unsigned int height = 720, const char* title = "GLFW window")
	{
		mGLFWwindow_uptr = GLFWwindow_uptr(glfwCreateWindow(width, height, title, NULL, NULL));
		if (getGLFWwindow() == NULL)
		{
			ERR("Failed to create GLFW window! Terminating GLFW!");
			glfwTerminate();
			return;
		}
		glfwSetInputMode(getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);	//GLFW_CURSOR_DISABLED = lock mouse in screen
	}
	
	void Window::activate()
	{
		glfwMakeContextCurrent(getGLFWwindow()); //set the GL context to this window
		glfwSetWindowUserPointer(getGLFWwindow(), this); //set GLFW to use this The5::window as object passed for callbacks
		glfwSetFramebufferSizeCallback(getGLFWwindow(), Window::windowResize_callback); //assign resize callback
		glfwSetWindowRefreshCallback(getGLFWwindow(), Window::windowRefresh_callback); //assign refresh callback
		glfwSwapInterval(1); // Enable vsync
	}

	void Window::initGLAD()
	{
		if (!mGLAD_initialized)
		{
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				ERR("Failed to initialize GLAD via gladLoadGLLoader()! Trying gladLoadGL()...");
				if (!gladLoadGL())
				{
					ERR("Failed tu use gladLoadGL()!");
					return;
				}
			}
		}
	}

	void Window::initGL()
	{
		if (!mGL_initialized)
		{
			//init debug context after context was set, requires "glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE)" to be set b4 GLFWwindow is created
			The5::GL::gl_initDebugContext();
		}
	}

//**************************************************//


	void Window::runGameLoop()
	{
		while (!glfwWindowShouldClose(getGLFWwindow()))
		{



			glfwSwapBuffers(getGLFWwindow());
			//Event processing must be done regularly while you have any windows and is normally done each frame after buffer swapping.
			//http://www.glfw.org/docs/latest/input_guide.html#events
			glfwPollEvents();
		}
	}

	void Window::terminate()
	{
		glfwSetWindowShouldClose(getGLFWwindow(), true);
	}

	GLFWwindow* Window::getGLFWwindow()
	{
		return mGLFWwindow_uptr.get();
	}


	void Window::setTitle(const char* title)
	{
		glfwSetWindowTitle(getGLFWwindow(), title);
		this->title = title;
	}

	void Window::resizeViewport(unsigned int width, unsigned int height)
	{
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
		this->height = height;
		this->width = width;
	}


	Window::~Window()
	{
		glfwSetWindowShouldClose(getGLFWwindow(), true);
		glfwTerminate();
	}

}

