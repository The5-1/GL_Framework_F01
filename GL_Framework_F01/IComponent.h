#pragma once

namespace The5 {


	enum ComponentType { Renderable };

	class Entity;

	class IComponent
	{
	public:

		IComponent(Entity* entity);

		//pure virtual
		virtual ComponentType getType() = 0;
		virtual void update() = 0;

		Entity* parentEntity;
	};

}