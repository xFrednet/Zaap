#pragma once

#include "graphics/Model.h"
#include "Common.h"
#include "graphics/camera/Camera.h"

namespace zaap { namespace graphics {

	class ZAAP_API Renderer
	{
	private:
		static Renderer* s_Instance;
	protected:
		//Init
		virtual void init() = 0;

		//Render
		virtual void render(Model* model) = 0;

		//Setters
		virtual void setCamera(Camera* camera) = 0;

		//Util
		virtual void prepare() = 0;
		virtual void cleanup() = 0;
		virtual void resize(uint width, uint height) = 0;

	public:
		//Init
		static void Init();

		//Render
		static void Render(Model* model);
		static void RenderModelArray(const std::vector<Model*>& models);
		
		//Setters
		static void SetCamera(Camera* camera);
		
		//Util
		static void Prepare();
		static void Cleanup();
		static void Resize(uint width, uint height);
	};

}}