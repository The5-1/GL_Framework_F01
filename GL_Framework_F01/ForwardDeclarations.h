#pragma once

#include <memory>
#include <vector>


struct GLFWwindow;

namespace The5
{
	//OpenGL & Rendering

	struct Vertex;

	class Mesh;
	typedef std::unique_ptr<Mesh> Mesh_uptr;

	class Texture;
	typedef std::unique_ptr<Texture> Texture_uptr;

	class Shader;
	typedef std::unique_ptr<Shader> Shader_uptr;

	class Material;
	typedef std::unique_ptr<Material> Material_uptr;


	//Main Application & Managers
	class Application;
	typedef std::unique_ptr<The5::Application> Application_uptr;

	class Window;
	typedef std::unique_ptr<The5::Window> Window_uptr;

	class InputManager;
	typedef std::unique_ptr<InputManager> InputManager_uptr;

	class AssetManager;
	typedef std::unique_ptr<AssetManager> AssetManager_uptr;

	class Renderer;
	typedef std::unique_ptr<Renderer> Renderer_uptr;

	//Scene, Entity & Component

	class Scene;
	typedef std::unique_ptr<The5::Scene> Scene_uptr;

	class Entity;
	typedef std::unique_ptr<The5::Entity> Entity_uptr;

	class IComponent;
	typedef std::unique_ptr<IComponent> Component_uptr;

	class Renderable;

}