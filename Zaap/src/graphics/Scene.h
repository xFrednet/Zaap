#pragma once

#include "Common.h"
#include "Types.h"

#include "Model.h"
#include "graphics/Renderer.h"

namespace zaap { namespace graphics {
	
	class ZAAP_API Scene
	{
	private:
	protected:
		std::vector<Model*> m_Models;

	public:

		virtual void addModel(Model* model);
		virtual void removeModel(Model* model);

		virtual void render() const;
		virtual void update() const;

	};
}}
