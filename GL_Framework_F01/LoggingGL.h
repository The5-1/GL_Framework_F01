#pragma once

#include "Logging.h"
#include "GL_include.h"

///Helper functions for OpenGL related Logging and Debugging
namespace The5 {
	namespace GL {

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
				//std::cerr << "GL CheckError:\t" << error << "\n\tFile: " << __FILE__ << "\n\tFuncion \"" << __func__ << "\" in Line " << __LINE__ << std::endl;
				ERR("GL_checkError:\n" << error);
			}
			return errorCode;
		}

#ifndef GL_checkError()
#define GL_checkError() glCheckError_(__FILE__, __LINE__) 
#endif // !GL_checkError()


		//const void *userParam needs to be const!! 
		//https://informatik-forum.at/showthread.php?108596-problem-mit-glDebugMessageCallback 
		//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDebugMessageCallback.xhtml
		void APIENTRY gl_DebugOutput_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
		{
			
			// ignore non-significant error/warning codes
			if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

			std::string errormessage = "\t";

			switch (source)
			{
			case GL_DEBUG_SOURCE_API:             errormessage += "Source: API"; break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   errormessage += "Source: Window System"; break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER: errormessage += "Source: Shader Compiler"; break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:     errormessage += "Source: Third Party"; break;
			case GL_DEBUG_SOURCE_APPLICATION:     errormessage += "Source: Application"; break;
			case GL_DEBUG_SOURCE_OTHER:           errormessage += "Source: Other"; break;
			}

			errormessage += "\n\t";

			switch (type)
			{
			case GL_DEBUG_TYPE_ERROR:               errormessage += "Type: Error"; break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: errormessage += "Type: Deprecated Behaviour"; break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  errormessage += "Type: Undefined Behaviour"; break;
			case GL_DEBUG_TYPE_PORTABILITY:         errormessage += "Type: Portability"; break;
			case GL_DEBUG_TYPE_PERFORMANCE:         errormessage += "Type: Performance"; break;
			case GL_DEBUG_TYPE_MARKER:              errormessage += "Type: Marker"; break;
			case GL_DEBUG_TYPE_PUSH_GROUP:          errormessage += "Type: Push Group"; break;
			case GL_DEBUG_TYPE_POP_GROUP:           errormessage += "Type: Pop Group"; break;
			case GL_DEBUG_TYPE_OTHER:               errormessage += "Type: Other"; break;
			}

			errormessage += "\n\t";

			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:         errormessage += "Severity: high"; break;
			case GL_DEBUG_SEVERITY_MEDIUM:       errormessage += "Severity: medium"; break;
			case GL_DEBUG_SEVERITY_LOW:          errormessage += "Severity: low"; break;
			case GL_DEBUG_SEVERITY_NOTIFICATION: errormessage += "Severity: notification"; break;
			} 

			errormessage += "\n\t";

			LOG("GL_DEBUG_OUTPUT ID: " << id << "\n\t"<< message << "\n" << errormessage);
		}

		void gl_initDebugContext()
		{
			// "glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE)" needs to be done before glfwCreateWindow
			GLint flags;
			glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
			if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
			{
				// initialize debug output
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(The5::GL::gl_DebugOutput_callback, nullptr);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE); //what kind of messages are allowed
			}
		}


		static void glfw_error_callback(int error, const char* description)
		{
			ERR("GLFW Error: " << error << " Desc: " << description);
		}


		//you can add custom prints to the Debug output
		//it is handled as a stack
		//normal printing seems just as fine..., pobably neede if you MUST have the error be thrown by the hardware?
		void gl_PushDebugGroup(const char* message)
		{
			glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, strlen(message), message);
		}

		void gl_PopDebugGroup()
		{
			glPopDebugGroup();
		}

	}
}