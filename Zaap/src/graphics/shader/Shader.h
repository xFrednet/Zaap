#pragma once

#include <Common.h>

#include <maths/Maths.h>
#include <graphics/Color.h>
#include <graphics/Material.h>

#ifdef ZA_SHADER_LIGHT_COUNT
#	if (ZA_SHADER_LIGHT_COUNT == 0) || (ZA_SHADER_LIGHT_COUNT > 8)
#		pragma message("ZAAP Error: zaap can only supports a ZA_SHADER_LIGHT_COUNT of 8 and lower (8 >= x > 0)")
#		undef ZA_SHADER_LIGHT_COUNT
#		define ZA_SHADER_LIGHT_COUNT 4
#	endif
#else
#	define ZA_SHADER_LIGHT_COUNT 4 //define if it is undefined
#endif

#ifdef ZA_SHADER_MATERIAL_COUNT
#	if (ZA_SHADER_MATERIAL_COUNT <= 0) || (ZA_SHADER_MATERIAL_COUNT > 16)
#		pragma message("ZAAP Error: zaap can only supports a ZA_SHADER_MATERIAL_COUNT of 16 and lower (16 >= x > 0)")
#		undef ZA_SHADER_MATERIAL_COUNT
#		define ZA_SHADER_MATERIAL_COUNT 8
#	endif
#else
#	define ZA_SHADER_MATERIAL_COUNT 8 //define if it is undefined
#endif


/* //////////////////////////////////////////////////////////////////////////////// */
// // Shader structs and values //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap { namespace graphics {
	
	typedef ZAAP_API struct ZA_GUI_VERTEX_ {
		Vec3 Position;
		uint Type;
		Vec4 TypeInfo;
	} ZA_GUI_VERTEX;

}}
/* //////////////////////////////////////////////////////////////////////////////// */
// // Shader buffers //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap { namespace graphics {
	
	// <Enum>
	//		ZA_SHADER_TYPE_
	//
	// <Descritpion>
	//		This enum can be used to point to a specific
	//		shader. It is used by the Renderer3D to request start and
	//		stop shader.
	//
	typedef ZAAP_API enum ZA_SHADER_TYPE_ {
		ZA_SHADER_UNKNOWN			= 0,
		ZA_SHADER_DEFAULT_SHADER	= 1,
		ZA_SHADER_TERRAIN_SHADER	= 2,
		ZA_SHADER_FONT_SHADER_2D	= 3,
		ZA_SHADER_GUI_SHADER		= 4
	} ZA_SHADER_TYPE;

	/* ********************************************************* */
	// * Vertex Shader buffers *
	/* ********************************************************* */

	// <Struct>
	//		ZA_VS_MATRIX_BUFFER
	//
	// <Description>
	//		This is a representation of a MatrixBuffer that is 
	//		used by some 3D shaders.
	//
	// <Note>
	//      The members are sorted after the multiplication order in
	//      the VertexShader.
	//
	// <Members>
	//		TransformationMatrix::
	//			The transformation matrix of the current model/mesh or 
	//			entity. This matrix controls the position, rotation and scale 
	//			of the rendered object. <\n>
	//			(This matrix is changed for every object that is rendered.);;
	//		ViewMatrix::
	//			The view matrix of the current camera. This moves the objects 
	//			according to camera position and rotation. <\n>
	//			(This matrix is/can be changed by the camera. This is usually 
	//			only done during a update but it is set/loaded at the start 
	//			of every frame);;
	//		ProjectionMatrix::
	//			The projection matrix of the current renderer. This scales the
	//			objects according to their position in the field of view. <\n>
	//			(This matrix is calculated and loaded by the renderer. This is done at the 
	//			initialization, after a resize event and/or for a special render goal.);;
	//
	typedef struct ZAAP_API ZA_VS_MATRIX_BUFFER_
	{
		Mat4 TransformationMatrix;
		Mat4 ViewMatrix;
		Mat4 ProjectionMatrix;
	} ZA_VS_MATRIX_BUFFER;

	// <Struct>
	//		ZA_VS_SCENE_BUFFER
	//
	// <Description>
	//		This holds some relevant information about the current 
	//		scene it is used by some 3D shaders.
	//
	// <Members>
	//		CameraPosition::
	//			This is the position of the current @Camera that is
	//			set in the loaded @Scene. <\n>
	//			(This is loaded at the start of every frame.);;
	//		VSSceneBufferPadding::
	//			Some padding to make the size dividable by 16.<\n>
	//			(This should never be touched.);;
	//
	typedef struct ZAAP_API ZA_VS_SCENE_BUFFER_ {
		Vec3 CameraPosition;
		float VSSceneBufferPadding;
	} ZA_VS_SCENE_BUFFER;

	/* ********************************************************* */
	// * Light buffers *
	/* ********************************************************* */
	
	// <Struct>
	//		ZA_VS_LIGHT_BUFFER
	//
	// <Description>
	//		This is a representation of a LightBuffer that is 
	//		used by some 3D VertexShaders.
	//
	// <Note>
	//		The size of this struct depends on ZA_SHADER_LIGHT_COUNT.
	//		It can be calculated like this: 16 + 16 * ZA_SHADER_LIGHT_COUNT.
	//
	// <Members>
	//		VSLightCount::
	//			The amount of lights that are loaded right now.
	//			The value is between 0 and ZA_SHADER_LIGHT_COUNT.<\n>
	//			(This is changed every time that the LightSetup is
	//			loaded. The @Scene class updates it's @LightSetup
	//			every frame.);;
	//		VSLightBufferPadding::
	//			This is some padding to make the total size dividable 
	//			by 16. That is a requirement of DirectX. <\n>
	//			(This is never changes, at least not to my knowledge...
	//			says the only developer.);;
	//		LightPositions::
	//			This is an array that keeps the position of the @Light s
	//			that are loaded to the shader. <\n>
	//			(This is changed every time that the LightSetup is
	//			loaded. The @Scene class updates it's @LightSetup
	//			every frame.<\n>
	//			Note that some old positions might remain
	//			in this array because the loaders usually only change the
	//			indices up to the light count.);;
	//
	typedef struct ZAAP_API ZA_VS_LIGHT_BUFFER_ {
		//16 Bytes
		uint VSLightCount;
		Vec3 VSLightBufferPadding;

		// 16 Bytes * ZA_SHADER_LIGHT_COUNT
		Vec4 LightPositions[ZA_SHADER_LIGHT_COUNT];
	} ZA_VS_LIGHT_BUFFER;

	// <Struct>
	//		ZA_PS_LIGHT_BUFFER
	//
	// <Description>
	//		This is a representation of a LightBuffer that is 
	//		used by some 3D PixelShaders.
	//
	// <Note>
	//		The size of this struct depends on ZA_SHADER_LIGHT_COUNT.
	//		It can be calculated like this: 16 + 16 * ZA_SHADER_LIGHT_COUNT or
	//		you could just use sizeof() but that would be boring I understand 
	//		that.
	//
	// <Members>
	//		PSLightCount::
	//			The amount of lights that are loaded right now.
	//			The value is between 0 and ZA_SHADER_LIGHT_COUNT.<\n>
	//			(This is changed every time that the LightSetup is
	//			loaded. The @Scene class updates it's @LightSetup
	//			every frame.);;
	//		AmbientLight::
	//			This is a Vector that keeps ambient lighting it is
	//			also used as some padding for the PSLightCount value.
	//			To make this struct dividable by 16. this is a requirement 
	//			of DirectX. <\n>
	//			(This also changes every time that the @LightSetup is loaded.
	//			I won't copy the text a third time... I mean: "I don't use
	//			copy and paste to write these notes.");;
	//		LightPositions::
	//			This is an array that keeps the position of the @Light s
	//			that are loaded to the shader. <\n>
	//			(This is changed every time that the LightSetup is
	//			loaded. The @Scene class updates it's @LightSetup
	//			every frame.<\n>
	//			Note that some old positions might remain
	//			in this array because the loaders usually only change the
	//			indices up to the light count.);;
	//
	typedef struct ZAAP_API ZA_PS_LIGHT_BUFFER_ {
		//16 Bytes
		uint PSLightCount;
		Vec3 AmbientLight;

		//16 Bytes * ZA_SHADER_LIGHT_COUNT
		Color LightColors[ZA_SHADER_LIGHT_COUNT];
	} ZA_PS_LIGHT_BUFFER;

	/* ********************************************************* */
	// * Material *
	/* ********************************************************* */

	// <Struct>
	//		ZA_PS_MATERIAL_BUFFER
	//
	// <Description>
	//		This struct represents the @Material buffer that is
	//		used by some pixel shaders.
	//
	// <Members>
	//		Materials::
	//			This is an array of Materials.
	//			The @Materials are used to calculate the effects
	//			that light sources have on the rendered meshes.<\n>
	//			(This buffer is changed for every object that is rendered.<\n>
	//			Note that some old materials might remain in this array
	//			because the loaders usually only change the @Materials that are 
	//			specific to the current object.);;
	//
	typedef struct ZAAP_API ZA_PS_MATERIAL_BUFFER_ {
		Material Materials[ZA_SHADER_MATERIAL_COUNT];
	} ZA_PS_MATERIAL_BUFFER;

	/* ********************************************************* */
	// * Other *
	/* ********************************************************* */
	
	// <Struct>
	//		ZA_PS_GUI_COLOR_BUFFER
	//
	// <Description>
	//		This struct hold some @Colors that are needed in
	//		the @GUIShader.
	//
	// <Members>
	//		TextColor::
	//			This is the color that will be used 
	//			for the rendered Font.;;
	//
	typedef struct ZAAP_API ZA_PS_GUI_COLOR_BUFFER_ {
		Color TextColor;
	} ZA_PS_GUI_COLOR_BUFFER;

}}

////////////////////////////////////////////////////////////////////////////////
// Shader class //
////////////////////////////////////////////////////////////////////////////////
namespace zaap { namespace graphics {
	
	// I left out the "API" namespace because I'm too lazy to type it every time
	// and yes i copped this line from the shader class... this raises the question
	// couldn't I just copy the API namespace every time? Yes I could shut up.

	// <Class>
	//      Shader
	//
	// <Description>
	//      This is a abstract class for all the other
	//      shader classes.
	//      
	class ZAAP_API Shader
	{
	public:
		// <Deconstructor>
		//      ~Shader
		//
		// <Description>
		//      This is a virtual deconstructor to support the deconstructors
		//      of the sub classes.
		//
		virtual ~Shader() {}

		// <Function>
		//      start
		//
		// <Description>
		//      This method starts the shader instance.
		//      This method is overridden by the API shaders.
		//      
		virtual void start() const = 0;
		
		// <Function>
		//      stop
		//
		// <Description>
		//      This method stops the shader instance.
		//      This method is overridden by the API shaders.
		//      
		virtual void stop() const = 0;

		// <Function>
		//      getShaderType
		//
		// <Description>
		//      This returns the current shader type.
		//      
		virtual ZA_SHADER_TYPE getShaderType() const = 0;
		
	};

}}
