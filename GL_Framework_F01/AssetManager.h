#pragma once

#include "stl_include.h"

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

namespace The5 {

	typedef std::unique_ptr<Mesh> Mesh_uptr;

	typedef std::unique_ptr<Texture> Texture_uptr;

	typedef std::unique_ptr<Shader> Shader_uptr;

	typedef std::unique_ptr<Material> Material_uptr;

	class AssetManager
	{
	public:

		AssetManager();

	private:
		std::vector<Mesh_uptr> mMeshes;
		std::vector<Texture_uptr> mTextures;
		std::vector<Shader_uptr> mShaders;
		std::vector<Material_uptr> mMaterials;

	};


}