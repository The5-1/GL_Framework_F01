#include "Scene.h"

#include "stl_include.h"

#include "Application.h"
#include "Entity.h"

namespace The5 {

	typedef std::unique_ptr<The5::Entity> Entity_uptr;

	Scene::Scene(std::string name, Application* application) : name(name), mApplication(application)
	{
		std::string rootname = name;
		rootname += "_root";
		mRoot = The5::Entity_uptr(new Entity(rootname, nullptr, mApplication));
	}


	Entity* Scene::getRoot()
	{
		return this->mRoot.get();
	}

	Application * Scene::getApplication()
	{
		return mApplication;
	}

}
