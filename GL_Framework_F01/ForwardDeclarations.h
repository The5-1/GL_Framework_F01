#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

struct GLFWwindow;

namespace The5
{
	//OpenGL & Rendering
	typedef glm::mat3 mat3;
	typedef glm::mat4 mat4;

	typedef glm::vec3 vec3;
	typedef glm::vec2 vec2;
	typedef unsigned int index;

	typedef std::vector<The5::vec3> vec3List;
	typedef std::vector<The5::vec2> vec2List;
	typedef std::vector<The5::index> indexList;

	struct Vertex;
	typedef std::vector<The5::Vertex> vertexList;

	class Mesh;
	typedef std::unique_ptr<The5::Mesh> Mesh_uptr;

	class Texture;
	typedef std::unique_ptr<The5::Texture> Texture_uptr;

	class Shader;
	typedef std::unique_ptr<The5::Shader> Shader_uptr;

	class Material;
	typedef std::unique_ptr<The5::Material> Material_uptr;


	//Main Application & Managers
	class Application;
	typedef std::unique_ptr<The5::Application> Application_uptr;

	class Window;
	typedef std::unique_ptr<The5::Window> Window_uptr;

	class InputManager;
	typedef std::unique_ptr<The5::InputManager> InputManager_uptr;

	class AssetManager;
	typedef std::unique_ptr<The5::AssetManager> AssetManager_uptr;


	//Entities
	class Scene;
	typedef std::unique_ptr<The5::Scene> Scene_uptr;

	class Entity;
	typedef std::unique_ptr<The5::Entity> Entity_uptr;

	//Components
	class IComponent;
	typedef std::unique_ptr<The5::IComponent> IComponent_uptr;

	class ComponentFactory;
	enum ComponentType { RenderableType, MoveableType };
	/*
	std::map<ComponentType, std::string> ComponentTypeString =	{
																	std::make_pair(ComponentType::RenderableType, "Renderable"), 
																	std::make_pair(ComponentType::MoveableType, "Moveable"),
																};
																*/
	
	class RenderableC;
	typedef std::unique_ptr<The5::RenderableC> RenderableC_uptr;

	class MoveableC;
	typedef std::unique_ptr<The5::MoveableC> MoveableC_uptr;

	//Component Processors
	class IComponentProcessor;
	typedef std::unique_ptr<The5::IComponent> IComponentProcessor_uptr;

	class RendererCP;
	typedef std::unique_ptr<The5::RendererCP> RendererCP_uptr;


}