#pragma once

#include "stl_include.h"
#include "ForwardDeclarations.h"
#include "Shader.h"

namespace The5 {
	//http://www.lighthouse3d.com/tutorials/glsl-tutorial/uniform-blocks/

	class IMaterial 
	{
	public:
		std::string name;

		IMaterial(std::string name, std::string vertexFile = "", std::string fragmentFile = "", 
			std::string tesselationControlFile = "", std::string tesselationEvaluationFile = "",
			std::string computeFile = ""
		) :
			name(name),
			vertexFile(vertexFile), fragmentFile(fragmentFile), 
			geometryFile(geometryFile), 
			tesselationControlFile(tesselationControlFile), tesselationEvaluationFile(tesselationEvaluationFile),
			computeFile(computeFile)
		{
			mShader = new Shader(name + "_shader", vertexFile, fragmentFile); //TODO: replace with call to AssetFactory
	
		};

		const std::string vertexFile;
		const std::string geometryFile;
		const std::string tesselationControlFile;
		const std::string tesselationEvaluationFile;
		const std::string fragmentFile;
		const std::string computeFile;

		/** Uniforms */
		//Dependend on concrete Implementation

		void recompileShader() {mShader->compileShader(vertexFile, fragmentFile);}

	protected:
		/** update the shader with the given uniforms */
		//virtual void updateShader() = 0;

		/** shader used by this material */
		Shader* mShader;


			
	};
}