#include "AssetManager.h"

namespace The5 {

	AssetManager::AssetManager()
	{
		mMeshes = std::vector<Mesh_uptr>();
		mTextures = std::vector<Texture_uptr>();
		mShaders = std::vector<Shader_uptr>();
		mMaterials = std::vector<Material_uptr>();
	}

}