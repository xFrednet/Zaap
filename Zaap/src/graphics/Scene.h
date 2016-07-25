#pragma once

#include <common.h>
#include <types.h>

#include <graphics/renderer.h>
#include <entity/Entity.h>

namespace zaap { namespace graphics {
	
	class ZAAP_API Scene
	{
	private:
	protected:
		std::vector<Entity*> m_Entities;

	public:

		virtual void addEntity(Entity* model);
		virtual void removeEntity(Entity* model);

		virtual void render() const;
		virtual void update() const;

	};
}}
