#pragma once

#include "stl_include.h"

namespace The5 {

	class Entity;
	typedef std::unique_ptr<The5::Entity> Entity_uptr;

	class Scene
	{
	public:

		std::string name;

		Scene(std::string name);

		Entity* getRoot();

	private:

		///one entity is the root, that then handles it's own children
		Entity_uptr mRoot;
	};
}
