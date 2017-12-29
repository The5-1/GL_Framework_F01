#pragma once
#include <string>

namespace The5
{
	//Paths, end with "/"
	const std::string PROJECT_PATH = "D:/Dev/Projects/GL_Framework_F01/GL_Framework_F01/";

	const std::string LOCAL_ASSET_PATH = PROJECT_PATH + "Assets/";
	const std::string GLOBAL_ASSET_PATH = "D:/Dev/Assets/";

	const std::string SHADER_PATH = LOCAL_ASSET_PATH + "Shaders/";
	const std::string DEFAULT_SHADER_VERT = SHADER_PATH + "default.vert.glsl";
	const std::string DEFAULT_SHADER_FRAG = SHADER_PATH + "default.frag.glsl";

	const std::string MESH_PATH = LOCAL_ASSET_PATH + "Meshes/";
}