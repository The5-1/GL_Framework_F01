#pragma once

#include "GL_include.h"
#include "Logging.h"

namespace The5 {
	namespace GL {

		///Helper functions for OpenGL related Logging and Debugging
		/********************************************************************************************************************************************************
		The old/tedious way of checking errors in openGL is to, manually test after every operation.
		You can check errors with this custom GL_CHECKERROR function here //https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetError.xhtml
		- No other errors are recorded until glGetError is called.
		- glGetError should always be called in a loop, until it returns GL_NO_ERROR, if all error flags are to be reset.
		To get more detailed error information, one still has to use dedicated functions that return specialized Error Enums:
		- glCheckFramebufferStatus(...) --> e.g. GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
		- glGetShaderInfoLog(GL_COMPILE_STATUS) --> e.g. GL_FALSE
		*********************************************************************************************************************************************************/


		//https://learnopengl.com/#!In-Practice/Debugging
		GLenum glCheckError_(const char *file, const char* function, int line)
		{
			GLenum errorCode;
			while ((errorCode = glGetError()) != GL_NO_ERROR)
			{
				std::string error;
				switch (errorCode)
				{
				//Flags for OpenGL 4 see: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetError.xhtml
				case GL_INVALID_ENUM:					error = "INVALID_ENUM"; break;
				case GL_INVALID_VALUE:					error = "INVALID_VALUE"; break;
				case GL_INVALID_OPERATION:				error = "INVALID_OPERATION"; break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:	error = "INVALID_FRAMEBUFFER_OPERATION"; break;
				case GL_OUT_OF_MEMORY:					error = "OUT_OF_MEMORY"; break;
				//case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
				//case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
				case default:							error = "some other error"; break;
				}
				//std::cerr << "GL CheckError:\t" << error << "\n\tFile: " << __FILE__ << "\n\tFuncion \"" << __func__ << "\" in Line " << __LINE__ << std::endl;
				ERR_GL("GL_CHECKERROR:\n" << error << "\n\tFile: " << file << "\n\tFuncion \"" << function << "\" in Line " << line << "\n\t(Note: You should rather use glEnable(GL_DEBUG_OUTPUT) than this manual error checking.)" << std::endl);
			}
			return errorCode;
		}

		//Define a macro that passes file and line
#ifndef GL_CHECKERROR()
#define GL_CHECKERROR() glCheckError_(__FILE__, __func__, __LINE__) 
#endif // !GL_CHECKERROR()

	}
}