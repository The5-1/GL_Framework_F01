#pragma once

#include <memory>
#include <vector>
#include <map>
#include <bitset>
#include <glm/glm.hpp>

#include "tree_include.h"

struct GLFWwindow;

namespace The5
{
	//OpenGL & Rendering
	using mat2 = glm::mat2;
	using mat3 = glm::mat3;
	using mat4 = glm::mat4;

	using vec2 = glm::vec2;
	using vec3 = glm::vec3;
	using vec4 = glm::vec4;
	using index = unsigned int;

	using vec3List = std::vector<The5::vec3>;
	using vec2List = std::vector<The5::vec2>;
	using indexList = std::vector<The5::index>;

	struct Vertex;
	using vertexList = std::vector<The5::Vertex>;

	class Mesh;
	using Mesh_uptr = std::unique_ptr<The5::Mesh>;

	class Texture;
	using Texture_uptr = std::unique_ptr<The5::Texture>;

	class RenderBuffer;
	using RenderBuffer_uptr = std::unique_ptr<The5::RenderBuffer>;
	//enum TextureBufferType { TextureBuffer, RenderBuffer };
	enum TextureAttachmentType { ColorAttachment, DepthAttachment, StencilAttachment };
	enum TextureFormatArchetype { noTextureFormatArchetype, R8, R16, R32, RGB8, RGB16, RGB32, RGBA8 };
	enum FBOArchetype { noFBOArchetype, FBO_RGBA8, FBO_RGBA8_Depth32, FBO_GBuffer8_Depth32};

	class Shader;
	using Shader_uptr = std::unique_ptr<The5::Shader>;

	class IMaterial;
	using IMaterial_uptr = std::unique_ptr<The5::IMaterial>;
	enum MaterialBlendMode { BlendDisabled, BlendAlpha, BlendPremultipliedAplha, BlendAdditive, BlendMultiplicative };
	enum MaterialDepthMode { DepthDisabled, DepthReadWrite, DepthReadOnly };

	//Main Application & Managers
	class Application;
	using Application_uptr = std::unique_ptr<The5::Application>;

	class Window;
	using Window_uptr = std::unique_ptr<The5::Window>;

	class InputManager;
	using InputManager_uptr = std::unique_ptr<The5::InputManager>;

	class AssetManager;
	using AssetManager_uptr = std::unique_ptr<The5::AssetManager>;

	//Asset
	class Image;
	using Image_uptr = std::unique_ptr<The5::Image>;

	class Model;
	using Model_uptr = std::unique_ptr<The5::Model>;

	//Rendering
	class RenderPass;
	using RenderPass_uptr = std::unique_ptr<The5::RenderPass>;

	class RenderTarget;
	using RenderTarget_uptr = std::unique_ptr<The5::RenderTarget>;

	class RendererCP;
	using RendererCP_uptr = std::unique_ptr<The5::RendererCP>;

	class RenderableC;
	using RenderableC_uptr = std::unique_ptr<The5::RenderableC>;

	//Entities
	class Scene;
	using Scene_uptr = std::unique_ptr<The5::Scene>;

	class Entity;
	using Entity_uptr = std::unique_ptr<The5::Entity>;

	//using SceneTree = Tree::tree<Entity_uptr>; //!!! tree h cant use uniqueptr because it has copy operators
	using SceneTree = Tree::tree<Entity*>;
	using SceneTree_uptr = std::unique_ptr<SceneTree>;

	//template <typename T> class tree;
	//using tree<Entity_uptr> SceneTree;
	//using std::unique_ptr<tree<Entity_uptr>> SceneTree_uptr;

	//Component
	class ComponentFactory;
	using ComponentFactory_uptr = std::unique_ptr<The5::ComponentFactory>;

	class IComponentProcessor;
	using IComponentProcessor_uptr = std::unique_ptr<The5::IComponentProcessor>;

	class IComponent;
	using IComponent_uptr = std::unique_ptr<The5::IComponent>;

	class MoveableC;
	using MoveableC_uptr = std::unique_ptr<The5::MoveableC>;

	class MoveableCP;
	using MoveableCP_uptr = std::unique_ptr<The5::MoveableCP>;

	/** total number of component types derived from IComonent*/
	const unsigned int COMPONENT_NUMBER = 5;

	/** enum to get Component Type at runtime */
	enum ComponentType { noComponent = 0, TransformationCType = 1, RenderableCType = 2, MoveableCType = 3, TimerCType = 4};

	/** enum to string for Component Types */	
	const std::map<ComponentType, std::string> ComponentTypeString {
		std::make_pair(ComponentType::TransformationCType, "TransformationComponent"),
		std::make_pair(ComponentType::RenderableCType, "RenderableComponent"),
		std::make_pair(ComponentType::MoveableCType, "MoveableComponent"),
		std::make_pair(ComponentType::TimerCType, "TimerComponent"),
	};

	/** enum to get Component Type at runtime */
	enum ComponentProcessorType { noComponentProcessor = 0, RendererCPType = 1, TimerCPType = 3};

	/** enum to string for Component Types */
	const std::map<ComponentProcessorType, std::string> ComponentProcessorTypeString{
		std::make_pair(ComponentProcessorType::RendererCPType, "RendererProcessor"),
		std::make_pair(ComponentProcessorType::TimerCPType, "TimerProcessor"),
	};
	
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
		bool isCompatible(const ComponentBitmask& required)
		{
			//"this" is the mask on the entity, it needs to have everything "required"
			// if(entity(011111) & required(011001) == required(011001))
			bool b = ((this->mask & required.mask) == required.mask);
			//std::cout <<(this->mask).to_string() << " & " << (required.mask).to_string() << " compatible: "  << b << std::endl;
			return b;
		}

		/** create a bitset with only the given ComponentTypes bit set [static] */
		static std::bitset<COMPONENT_NUMBER> getComponentTypeMask(ComponentType type)
		{
			std::bitset<COMPONENT_NUMBER> mask;

			if (type == ComponentType::noComponent)
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