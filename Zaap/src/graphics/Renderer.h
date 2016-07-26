#pragma once

#include "Common.h"
#include "graphics/camera/Camera.h"
#include <entity/Entity.h>

namespace zaap { namespace graphics {
	class Light;

	class ZAAP_API Renderer
	{
	private:
		static Renderer* s_Instance;
	protected:
		//Init
		virtual void init() = 0;

		//Render
		virtual void render(Entity* model) = 0;

		//Setters
		virtual void setCamera(Camera* camera) = 0;
		virtual void loadLight(Light* light) = 0;

		//Util
		virtual void prepare() = 0;
		virtual void cleanup() = 0;
		virtual void resize(uint width, uint height) = 0;

	public:
		//Init
		static void Init();

		//Render
		static void Render(Entity* model);
		static void RenderEntityArray(const std::vector<Entity*>& models);
		
		//Setters
		static void SetCamera(Camera* camera);
		static void LoadLight(Light* light);

		//Util
		static void Prepare();
		static void Cleanup();
		static void Resize(uint width, uint height);
	};

}}
