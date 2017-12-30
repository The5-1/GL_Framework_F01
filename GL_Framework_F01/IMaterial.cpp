#include "IMaterial.h"
#include "Shader.h"

namespace The5
{
	IMaterial::IMaterial(std::string name, Shader* shader): name(name), mShader(shader)
	{
		
	};

	Shader* IMaterial::createShader(
		std::string vertexFile, std::string fragmentFile,
		std::string geometryFile,
		std::string tesselationControlFile, std::string tesselationEvaluationFile,
		std::string computeFile)
	{
		//TODO: replace with call to AssetFactory
		mShader = new Shader(this->name + "_shader", vertexFile, fragmentFile); 
		return mShader;
	}

	void IMaterial::setShader(Shader * shader)
	{
		//delete(mShader); //Asset manager should own all shaders
		mShader = shader;
	}

	Shader * IMaterial::getShader()
	{
		return mShader;
	}

	void IMaterial::useShader()
	{
		this->mShader->use();
	}

	void IMaterial::setRecompileShader()
	{
		if(mShader != nullptr) mShader->setFlagRecompileShader();
	}

	void IMaterial::checkRecompileShader()
	{
		if(mShader != nullptr) mShader->checkRecompileShader();
	}

	void IMaterial::checkUpdateUniforms()
	{
		if (flagUniformsDirty)
		{
			updateUniforms();
			flagUniformsDirty = false;
		}
	}

	void IMaterial::updateUniforms()
	{
		mShader->uniform("uObjectColor", glm::vec4(uObjectColor));
	}

}