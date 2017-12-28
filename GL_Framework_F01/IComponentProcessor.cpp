#include "IComponentProcessor.h"
#include "IComponent.h"
#include "Entity.h"
#include "Scene.h"

namespace The5
{
	IComponentProcessor::IComponentProcessor(Application * application, ComponentBitmask mask) : mApplication(application) , mRequiredComponentBitmask(mask)
	{

	}

	bool IComponentProcessor::checkComponentsCompatible(Entity * entity)
	{
		return entity->checkComponentBitmaskCompatible(this->mRequiredComponentBitmask);
	}

	void IComponentProcessor::processEntity(Entity * entity)
	{
		if (checkComponentsCompatible(entity)) doProcessing(entity);
	}

	void IComponentProcessor::processScene(Scene * scene)
	{
		SceneTree* sceneTree = scene->getSceneTree();

		for (SceneTree::iterator it = sceneTree->begin(); it != sceneTree->end(); ++it)
		{
			Entity* e = it.node->data;
			processEntity(e);
		}
	}

	/*
	ComponentBitmask IComponentProcessor::initRequiredComponentBitmask()
	{
		//other classes need to implement the appropriate mask
		ComponentBitmask mask;
		return mask;
	}

	void IComponentProcessor::processEntity(Entity * entity)
	{

	}

	void IComponentProcessor::processScene(Scene * scene)
	{

	}
	*/






	/*
	//template class definitions must be in the header
	//https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c

	template <typename T> IComponentProcessor<T>::IComponentProcessor(Application* application): application(application)
	{
		//static_assert(std::is_base_of<BaseClass, Derived>::value, "IComponentPocessor must use a Type derived from IComponent!");
	}

	//TODO: Fix these, understand inheritance: how do i make a derived class call the base classes function but in its own derived context

	template <typename T> T* IComponentProcessor<T>::getComponent(unsigned int i)
	{
		return IComponentProcessor<T>::mComponentPointers.at(i);
	}

	template <typename T> void IComponentProcessor<T>::registerComponentPointer(T* component)
	{
		IComponentProcessor<T>::mComponentPointers.push_back(component);
	}

	template <typename T> void IComponentProcessor<T>::removeComponentPointer(T* component)
	{
		//https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
		//https://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
		IComponentProcessor<T>::mComponentPointers.erase(std::remove(mComponentPointers.begin(), mComponentPointers.end(), component), mComponentPointers.end());
	}
	*/


	/*

	//template definitions must be in the header
	//https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c

	///The Entity owns the Component
	///A Component signs itself up with a Component Processor
	//TODO: Problem: IComponentProcessor<Renderable> and IComponentProcessor<Moveable> have nothing in common and will just be 2 different classes after compile time

	//!!! when a std::vector<Base*> takes a vector to a pointer of base, maybe i need to do the same here???

	template<typename T>
	class IComponentProcessor
	{
	public:

		IComponentProcessor(Application* application) : mApplication(application)
		{
			//mComponentPointers = std::vector<T>();
		}

		T getComponent(unsigned int i)
		{
			return mComponentPointers.at(i);
		}

		void registerComponentPointer(T component)
		{
			mComponentPointers.push_back(component); //TODO this here crashes, implement IComponent::getComponentProcessor
		}

		void removeComponentPointer(T component)
		{
			//https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
			//https://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
			mComponentPointers.erase(std::remove(mComponentPointers.begin(), mComponentPointers.end(), component), mComponentPointers.end());
		}

	protected:

		///The Entity owns the component! No unique_ptr here!
		Application* mApplication;
		std::vector<T> mComponentPointers;
	};
	*/



}