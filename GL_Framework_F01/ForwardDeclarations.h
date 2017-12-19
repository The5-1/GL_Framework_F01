#pragma once

#include <memory>
#include <vector>


struct GLFWwindow;

namespace The5
{
	class Application;
	typedef std::unique_ptr<The5::Application> Application_uptr;

	class Window;
	typedef std::unique_ptr<The5::Window> Window_uptr;

	class Scene;
	typedef std::unique_ptr<The5::Scene> Scene_uptr;

	class AssetManager;
	typedef std::unique_ptr<AssetManager> AssetManager_uptr;

	class Renderer;
	typedef std::unique_ptr<Renderer> Renderer_uptr;


	class Mesh;
	typedef std::unique_ptr<Mesh> Mesh_uptr;

	class Texture;
	typedef std::unique_ptr<Texture> Texture_uptr;

	class Shader;
	typedef std::unique_ptr<Shader> Shader_uptr;

	class Material;
	typedef std::unique_ptr<Material> Material_uptr;

	class Entity;
	typedef std::unique_ptr<The5::Entity> Entity_uptr;


}