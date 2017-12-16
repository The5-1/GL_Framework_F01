#include "GL_init.h"

#include <string>
#include <iostream>
#include "GL_include.h"
#include "Logging.h"

namespace The5
{
	namespace GL
	{
		//https://learnopengl.com/#!In-Practice/Debugging
		GLenum glCheckError_(const char *file, int line)
		{
			GLenum errorCode;
			while ((errorCode = glGetError()) != GL_NO_ERROR)
			{
				std::string error;
				switch (errorCode)
				{
				case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
				case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
				case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
					//case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
					//case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
				case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
				case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
				}
				std::cerr << "GL CheckError:\t" << error << "\n\tFile: " << __FILE__ << "\n\tFuncion \"" << __func__ << "\" in Line " << __LINE__ << std::endl;
			}
			return errorCode;
		}

#ifndef GL_checkError()
#define GL_checkError() glCheckError_(__FILE__, __LINE__) 
#endif // !GL_checkError()

		void APIENTRY gl_DebugOutput_callback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar *message,
			const void *userParam) //this needs to be const!! https://informatik-forum.at/showthread.php?108596-problem-mit-glDebugMessageCallback and https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDebugMessageCallback.xhtml
		{
			// ignore non-significant error/warning codes
			if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

			std::cout << "---------------" << std::endl;
			std::cout << "Debug message (" << id << "): " << message << std::endl;

			switch (source)
			{
			case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
			case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
			case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
			} std::cout << std::endl;

			switch (type)
			{
			case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
			case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
			case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
			case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
			case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
			case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
			case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
			} std::cout << std::endl;

			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
			case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
			case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
			case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
			} std::cout << std::endl;
			std::cout << std::endl;
		}


		static void glfw_error_callback(int error, const char* description)
		{
			ERR("GLFW Error: " << error << " Desc: " << description);
		}




		// glfw: whenever the window size changed (by OS or user resize) this callback function executes
		// ---------------------------------------------------------------------------------------------
		void glfw_windowsize_callback(GLFWwindow* window, int width, int height)
		{
			// make sure the viewport matches the new window dimensions; note that width and 
			// height will be significantly larger than specified on retina displays.
			glViewport(0, 0, width, height);
		}

		int initGLAD()
		{
			// glad: load all OpenGL function pointers
			// ---------------------------------------
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				ERR("Failed to initialize GLAD via gladLoadGLLoader()! Trying gladLoadGL()...");
				if (!gladLoadGL())
				{
					ERR("Failed tu use gladLoadGL()!");
					return -1;
				}
			}


			return 1;
		}


		int initGLFW()
		{
			if (!glfwInit())
			{
				ERR("Failed to init GLFW!");
				return -1;
			}
			return 1;
		}

		GLFWwindow* initWindow(unsigned int width = 1024, unsigned int height = 720, const char* title = "GLFW window")
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
			glfwMakeContextCurrent(window); //GL context!
			if (window == NULL)
			{
				ERR("Failed to create GLFW window!");
				glfwTerminate();
				return nullptr;
			}
			glfwSetErrorCallback(glfw_error_callback);

			glfwSetFramebufferSizeCallback(window, glfw_windowsize_callback);	//resize callback
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	// tell GLFW to capture our mouse
			glfwSwapInterval(1);	// Enable vsync

			return window;
		}

		int initDebugContext()
		{
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
			GLint flags;
			glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
			if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
			{
				// initialize debug output
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(gl_DebugOutput_callback, nullptr);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
			}

			return 1;
		}


		GLFWwindow* initGL(unsigned int width = 1024, unsigned int height = 720, const char* title = "GLFW window")
		{
			initGLFW();
			GLFWwindow* window = initWindow(width, height, title);
			initGLAD(); //needs window as context
			initDebugContext();

			return window;
		}


	}
}