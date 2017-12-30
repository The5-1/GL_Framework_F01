#pragma once

#include "GL_include.h"
#include "Logging.h"

namespace The5 {
	namespace GL {

		///Helper functions for OpenGL and GLFW related Logging and Debugging
		/********************************************************************************************************************************************************
		Istead of using glGetError(), OpenGL 4.3 provides a callback that is called when OpenGL raises an Error.
		It does everything glGetError() does!
		But it is __not__ as detailed as testing for specific errors, like:
		- glCheckFramebufferStatus(...) --> e.g. GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
		- glGetShaderInfoLog(GL_COMPILE_STATUS) --> e.g. GL_FALSE
		Steps:
		1.) GLFW provide glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); before glfwCreateWindow()
		2.) set GLFW context and init GLAD
		3.) call the custom function gl_initDebugContext()
		    internally this calls glEnable(GL_DEBUG_OUTPUT); glDebugMessageCallback(myCallback);
		*********************************************************************************************************************************************************/

		void APIENTRY gl_DebugOutput_callback(
			GLenum source, GLenum type, GLuint id, GLenum severity, 
			GLsizei length, const GLchar *message, 
			const void *userParam) //const void *userParam needs to be const!! //https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDebugMessageCallback.xhtml
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

			ERR_GL("GL_DEBUG_OUTPUT ID: " << id << "\n\t" << message << "\n" << errormessage);
		}

		void gl_initDebugContext()
		{
			///requires KHR_debug: Core since OpenGL 4.3
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
				LOG("OpenGL GL_DEBUG_OUTPUT initialized.");
			}
			else
			{
				ERR_GL("Something went wrong setting GL_DEBUG_OUTPUT");
			}
		}


		static void glfw_error_callback(int error, const char* description)
		{
			ERR_GL("GLFW error: " << error << " Desc: " << description);
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