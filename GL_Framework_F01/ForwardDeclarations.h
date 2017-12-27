#pragma once

#include <memory>
#include <vector>
#include <map>
#include <bitset>
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

	//Component
	class ComponentManager;
	typedef std::unique_ptr<The5::ComponentManager> ComponentManager_uptr;

	//template<typename T> class IComponentProcessor;
	class IComponentProcessor;
	typedef std::unique_ptr<The5::IComponentProcessor> IComponentProcessor_uptr;

	class IComponent;
	typedef std::unique_ptr<The5::IComponent> IComponent_uptr;
	//template<typename T> class IComponent;

	class RendererCP;
	typedef std::unique_ptr<The5::RendererCP> RendererCP_uptr;
	
	class RenderableC;
	typedef std::unique_ptr<The5::RenderableC> RenderableC_uptr;

	class MoveableC;
	typedef std::unique_ptr<The5::MoveableC> MoveableC_uptr;

	class MoveableCP;
	typedef std::unique_ptr<The5::MoveableCP> MoveableCP_uptr;




	/** total number of component types derived from IComonent*/
	const unsigned int COMPONENT_NUMBER = 2;

	/** enum to get Component Type at runtime */
	enum ComponentType { none = 0, RenderableType = 1, MoveableType = 2 };

	/** enum to string for Component Types */
	/*
	std::map<ComponentType, std::string> ComponentTypeString = {
		std::make_pair(ComponentType::RenderableType, "Renderable"),
		std::make_pair(ComponentType::MoveableType, "Moveable"),
	};
	*/

	/** Bitmask that holds what component types are present/required for fast checking, based on std::bitmask */
	class ComponentBitmask
	{
	public:
		/** the bitmask */
		std::bitset<COMPONENT_NUMBER> mask;

		ComponentBitmask()
		{
			mask.reset();
		}

		/** set bitmask bit by ComponentType index */
		void addComponentType(ComponentType type)
		{
			mask.set(size_t(type - 1));
		}

		/** reset bitmask bit by ComponentType index */
		void removeComponentType(ComponentType type)
		{
			mask.reset(size_t(type - 1));
		}

		/** check if both bitmasks are identical */
		bool isEqual(const ComponentBitmask& other)
		{
			return (this->mask == other.mask);
		}

		/** check if this maks has all its bits represented in the other */
		bool isCompatible(const ComponentBitmask& other)
		{
			//if( (0110 AND 0111) == 0110)
			return ((this->mask & other.mask) == this->mask);
		}

		/** create a bitset with only the given ComponentTypes bit set [static] */
		static std::bitset<COMPONENT_NUMBER> getComponentTypeMask(ComponentType type)
		{
			std::bitset<COMPONENT_NUMBER> mask;

			if (type == ComponentType::none)
			{
				return mask;
			}
			else
			{
				mask.set(type - 1);
				return mask;
			}
		}

		/** binary | operator to combine bitmasks */
		ComponentBitmask& operator|(const ComponentType type)
		{
			this->addComponentType(type);
			return *this;
		}

		/** binarly |= opearator to combine bitmasks */
		ComponentBitmask& operator|=(const ComponentType type)
		{
			this->addComponentType(type);
			return *this;
		}

		/** return printable string */
		std::string to_string()
		{
			return mask.to_string();
		}

	};


}