#pragma once

#include "GL_include.h"
#include "stl_include.h"
#include "Logging.h"

namespace The5 {

	enum ShaderUniformType { uInt, uFloat, uVec2, uVec3, uMat3, uMat4};


	class Shader
	{
	public:
		unsigned int ID;
		std::string name;

		Shader(std::string name, std::string vertexPath, std::string fragmentPath) : name(name)
		{
			// 1. retrieve the vertex/fragment source code from filePath
			std::string vertexCode;
			std::string fragmentCode;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;

			// ensure ifstream objects can throw exceptions:
			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			try
			{
				// open files
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);
				std::stringstream vShaderStream, fShaderStream;
				// read file's buffer contents into streams
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();
				// close file handlers
				vShaderFile.close();
				fShaderFile.close();
				// convert stream into string
				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				ERR_GL("Failed to open Vertex Shader Files from:" << vertexPath);
				ERR_GL("Failed to open Fragment Shader Files from:" << fragmentPath);
			}
			const char* vShaderCode = vertexCode.c_str();
			const char * fShaderCode = fragmentCode.c_str();
			// 2. compile shaders
			unsigned int vertex, fragment;
			int success;
			char infoLog[512];
			// vertex shader
			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);
			checkCompileErrors(vertex, "VERTEX");
			// fragment Shader
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);
			checkCompileErrors(fragment, "FRAGMENT");
			// shader Program
			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);
			checkCompileErrors(ID, "PROGRAM");
			// delete the shaders as they're linked into our program now and no longer necessary
			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}
		// activate the shader
		// ------------------------------------------------------------------------
		
		//TODO: instead use https://www.khronos.org/opengl/wiki/Uniform_Buffer_Object
		//https://gamedev.stackexchange.com/questions/133615/how-do-you-store-uniform-data
		std::map<std::pair<ShaderUniformType, std::string>, unsigned int> uniforms;
		
		void use()
		{
			glUseProgram(ID);
		}

		void getUniforms()
		{
			//https://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade
			GLint i;
			GLint count;

			GLint size; // size of the variable
			GLenum type; // type of the variable (float, vec3 or mat4, etc)

			const GLsizei bufSize = 32; // maximum name length
			GLchar name[bufSize]; // variable name in GLSL
			GLsizei length; // name length

			glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &count);
			LOG("Shader \"" << this->name << "\" active Uniforms: " << count);
			//printf("Active Uniforms in Shader:  %d\n", count);

			for (i = 0; i < count; i++)
			{
				glGetActiveUniform(ID, (GLuint)i, bufSize, &length, &size, &type, name);

				LOG(" " << i << ") type: " << type << " name: " << name);
				//printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
			}
		}

		void getAttributes()
		{
			GLint i;
			GLint count;

			GLint size; // size of the variable
			GLenum type; // type of the variable (float, vec3 or mat4, etc)

			const GLsizei bufSize = 32; // maximum name length
			GLchar name[bufSize]; // variable name in GLSL
			GLsizei length; // name length

			glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTES, &count);
			LOG("Shader \"" << this->name << "\" active Attributes: " << count);
			//printf("Active Attributes: %d\n", count);

			for (i = 0; i < count; i++)
			{
				glGetActiveAttrib(ID, (GLuint)i, bufSize, &length, &size, &type, name);
				LOG(" " << i << ") type: " << type << " name: " << name);
				//printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
			}
		}

		void getShaderInterface()
		{
			//GL4.3
			//Extension: ARB_program_interface_query
			GLint numActiveAttribs = 0;
			GLint numActiveUniforms = 0;
			glGetProgramInterfaceiv(ID, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);
			glGetProgramInterfaceiv(ID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numActiveUniforms);

			std::vector<GLchar> nameData(256);
			for (int unif = 0; unif < numActiveUniforms; ++unif)
			{
				GLint arraySize = 0;
				GLenum type = 0;
				GLsizei actualLength = 0;
				glGetActiveUniform(ID, unif, nameData.size(), &actualLength, &arraySize, &type, &nameData[0]);
				std::string name((char*)&nameData[0], actualLength - 1);
				LOG(name);
			}
		}

		GLint getUniformLocation(const std::string &uniformName) const
		{
			GLint location = glGetUniformLocation(ID, uniformName.c_str());
			if (location == -1)
			{
				ERR_GL("Uniform \"" << uniformName.c_str() << "\" does not exist in shader \"" << this->name << "\"!\n\tCheck for typos, or if the variable is unused!");
			}
			return location;
		}

		// utility uniform functions
		// ------------------------------------------------------------------------
		void uniform(const std::string &uniformName, bool value) const
		{
			glUniform1i(getUniformLocation(uniformName), (int)value);
		}
		// ------------------------------------------------------------------------
		void uniform(const std::string &uniformName, int value) const
		{
			//checkUniform(uniformName);
			glUniform1i(getUniformLocation(uniformName), value);
		}
		// ------------------------------------------------------------------------
		void uniform(const std::string &uniformName, float value) const
		{
			//checkUniform(uniformName);
			glUniform1f(getUniformLocation(uniformName), value);
		}
		// ------------------------------------------------------------------------
		void uniform(const std::string &uniformName, const glm::vec2 &value) const
		{
			//checkUniform(uniformName);
			glUniform2fv(getUniformLocation(uniformName), 1, &value[0]);
		}
		void uniform(const std::string &uniformName, float x, float y) const
		{
			//checkUniform(uniformName);
			glUniform2f(getUniformLocation(uniformName), x, y);
		}
		// ------------------------------------------------------------------------
		void uniform(const std::string &uniformName, const glm::vec3 &value) const
		{
			//checkUniform(uniformName);
			glUniform3fv(getUniformLocation(uniformName), 1, &value[0]);
		}
		void uniform(const std::string &uniformName, float x, float y, float z) const
		{
			//checkUniform(uniformName);
			glUniform3f(getUniformLocation(uniformName), x, y, z);
		}
		// ------------------------------------------------------------------------
		void uniform(const std::string &uniformName, const glm::vec4 &value) const
		{
			//checkUniform(uniformName);
			glUniform4fv(getUniformLocation(uniformName), 1, &value[0]);
		}
		void uniform(const std::string &uniformName, float x, float y, float z, float w)
		{
			//checkUniform(uniformName);
			glUniform4f(getUniformLocation(uniformName), x, y, z, w);
		}
		// ------------------------------------------------------------------------
		void uniform(const std::string &uniformName, const glm::mat2 &mat) const
		{
			//checkUniform(uniformName);
			glUniformMatrix2fv(getUniformLocation(uniformName), 1, GL_FALSE, &mat[0][0]);
		}
		// ------------------------------------------------------------------------
		void uniform(const std::string &uniformName, const glm::mat3 &mat) const
		{
			//checkUniform(uniformName);
			glUniformMatrix3fv(getUniformLocation(uniformName), 1, GL_FALSE, &mat[0][0]);
		}
		// ------------------------------------------------------------------------
		void uniform(const std::string &uniformName, const glm::mat4 &mat) const
		{
			//checkUniform(uniformName);
			glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, &mat[0][0]);
		}

	private:
		// utility function for checking shader compilation/linking errors.
		// ------------------------------------------------------------------------
		void checkCompileErrors(unsigned int shader, std::string type)
		{
			int success;
			char infoLog[1024];
			if (type != "PROGRAM")
			{
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(shader, 1024, NULL, infoLog);
					//std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
					ERR_GL("SHADER_COMPILATION_ERROR of type : " << type << "\n" << infoLog << "\n");
				}
			}
			else
			{
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success)
				{
					glGetProgramInfoLog(shader, 1024, NULL, infoLog);
					//std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
					ERR_GL("PROGRAM_LINKING_ERROR of type : " << type << "\n" << infoLog << "\n");
				}
			}
		}
	};
}