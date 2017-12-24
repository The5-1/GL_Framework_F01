#pragma once

#include "stl_include.h"

#include "ForwardDeclarations.h"

namespace The5 {

	class Scene
	{
	public:
		Scene(std::string name, Application* application);

		std::string name;

		Entity* getRoot();

		Application* getApplication();

	private:

		///one entity is the root, that then handles it's own children
		Entity_uptr mRoot;
		Application* mApplication;

	};
}
