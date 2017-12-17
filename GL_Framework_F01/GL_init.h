#pragma once

#include <string>
#include <iostream>
#include "GL_include.h"
#include "Logging.h"

namespace The5 
{
	namespace GL
	{
		//https://learnopengl.com/#!In-Practice/Debugging
		GLenum glCheckError_(const char *file, int line);

#ifndef GL_checkError()
	#define GL_checkError() glCheckError_(__FILE__, __LINE__) 
#endif // !GL_checkError()

		void APIENTRY gl_DebugOutput_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

		static void glfw_error_callback(int error, const char* description);

		void glfw_windowsize_callback(GLFWwindow* window, int width, int height);

		static void glfw_key_wrapper_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		int initGLAD();

		int initGLFW();

		GLFWwindow* initWindow(unsigned int width, unsigned int height, const char* title);

		int initDebugContext();

		GLFWwindow* initGL(unsigned int width, unsigned int height, const char* title);
	}
}