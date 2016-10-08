#pragma once

#include <Common.h>
#include <Types.h>
#include <maths/Mat4.h>
#include <graphics/Color.h>

#ifdef ZAAP_SHADER_LIGHT_COUNT
#	if (ZAAP_SHADER_LIGHT_COUNT == 0) || (ZAAP_SHADER_LIGHT_COUNT > 8)
#		pragma message("ZAAP Error: zaap can only supports a ZAAP_SHADER_LIGHT_COUNT of 8 and lower (8 >= x > 0)")
#		undef ZAAP_SHADER_LIGHT_COUNT
#		define ZAAP_SHADER_LIGHT_COUNT 4
#	endif
#else
#	define ZAAP_SHADER_LIGHT_COUNT 4 //define if it is undefined
#endif

#ifdef ZAAP_SHADER_MATERIAL_COUNT
#	if (ZAAP_SHADER_MATERIAL_COUNT <= 0) || (ZAAP_SHADER_MATERIAL_COUNT > 16)
#		pragma message("ZAAP Error: zaap can only supports a ZAAP_SHADER_MATERIAL_COUNT of 16 and lower (16 >= x > 0)")
#		undef ZAAP_SHADER_MATERIAL_COUNT
#		define ZAAP_SHADER_MATERIAL_COUNT 8
#	endif
#else
#	define ZAAP_SHADER_MATERIAL_COUNT 8 //define if it is undefined
#endif

namespace zaap { namespace graphics {
	
	class ZAAP_API Shader
	{
	private:
	protected:
	public:
		virtual ~Shader()
		{
		}

		//
		// Matrix buffer
		//
		struct ZAAP_API ZA_VS_MATRIX_BUFFER
		{
			math::Mat4 ProjectionMatrix;
			math::Mat4 TransformationMatrix;
			math::Mat4 ViewMatrix;
		};

		//
		// Light buffer
		//
		struct ZAAP_API ZA_VS_LIGHT_BUFFER {
			//4 Bytes
		public:
			uint VSLightCount;
		private:
			math::Vec3 padding;
		
			//4 Bytes * ZAAP_SHADER_LIGHT_COUNT
		public:
			math::Vec4 LightPositions[ZAAP_SHADER_LIGHT_COUNT];
		};
		struct ZAAP_API ZA_PS_LIGHT_BUFFER {
		public:
			
			//4 Bytes
			uint PSLightCount;
			math::Vec3 AmbientLight;

			//4 Bytes * ZAAP_SHADER_LIGHT_COUNT
			Color LightColors[ZAAP_SHADER_LIGHT_COUNT];
		};

		// 
		// Scene buffer
		//
		// A buffer to hold shader information from the current scene.
		struct ZAAP_API ZA_VS_SCENE_BUFFER {
			math::Vec3 CameraPosition;
		private:
			float padding = 0;
		};

		//
		// Material buffer
		//
		// The material struct that holds the information about the single materials
		struct ZAAP_API ZA_PS_SHADER_MATERIAL {
			math::Vec3 Color;
			float Reflectivity;
		};
		//This struct represents the actual buffer that is loaded
		//in the pixel shader
		struct ZAAP_API ZA_PS_MATERIAL_BUFFER {
			ZA_PS_SHADER_MATERIAL Materials[ZAAP_SHADER_MATERIAL_COUNT];
		};


		virtual void start() const = 0;
		virtual void stop() const = 0;

		virtual void cleanup() = 0;
	};

}}
