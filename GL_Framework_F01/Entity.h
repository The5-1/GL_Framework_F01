#pragma once

#include "stl_include.h"
#include "IComponent.h"
#include "GL_include.h"


namespace The5 {

	class Entity
	{
	public:

		std::string name; //some non-unique name

		glm::mat4 transformation; //every entity exists in our scene, but must not be renderable (everything that does not is a global manager)

		std::unique_ptr<std::vector<IComponent>> components;

		std::unique_ptr<std::vector<Entity>> childs;


		Entity()
		{
			name = "";
			transformation = glm::mat4(1.0f);
			components = std::unique_ptr<std::vector<IComponent>>();
			childs = std::unique_ptr<std::vector<Entity>>();
		}

	private:


	};

}