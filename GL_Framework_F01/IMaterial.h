#pragma once

#include "stl_include.h"
#include "ForwardDeclarations.h"

namespace The5 {
	//http://www.lighthouse3d.com/tutorials/glsl-tutorial/uniform-blocks/

	class IMaterial 
	{
	public:
		std::string name;

		///Uniforms
		vec4 uObjectColor;

		IMaterial(std::string name, std::string vertexFile = "", std::string fragmentFile = "",
			std::string tesselationControlFile = "", std::string tesselationEvaluationFile = "",
			std::string computeFile = ""
		);

		std::string vertexFile;
		std::string geometryFile;
		std::string tesselationControlFile;
		std::string tesselationEvaluationFile;
		std::string fragmentFile;
		std::string computeFile;

		/** Uniforms */
		//Dependend on concrete Implementation

		void setShader(Shader* shader);
		Shader* createShader();
		Shader* getShader();
		void useShader();
		void setRecompileShader();
		void checkRecompileShader();

	protected:
		/** uniforms need refreshing */
		bool flagUniformsDirty = false;
		/** perfrom uniform refreshing */
		void checkUpdateUniforms();
		/** update the shader with the given uniforms */
		virtual void updateUniforms();


		/** shader used by this material */
		Shader* mShader;		
	};
}