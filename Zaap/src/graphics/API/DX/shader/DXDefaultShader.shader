
/* //////////////////////////////////////////////////////////////////////////////// */
// // Macros //
/* //////////////////////////////////////////////////////////////////////////////// */
// Macros have to be set in the loading process
#define ZA_LIGHT_COUNT    ZA_SHADER_LIGHT_COUNT
#define ZA_MATERIAL_COUNT ZA_SHADER_MATERIAL_COUNT

/* //////////////////////////////////////////////////////////////////////////////// */
/* ///Input/Output //
/* //////////////////////////////////////////////////////////////////////////////// */
struct ZA_VS_INPUT {
	float4 Position			: POSITION;
	float4 Normal			: NORMAL;
	float2 TexCoord			: TEXCOORD;
	uint   MaterialIndex	: MATERIAL;
};

struct ZA_VS_OUTPUT {
	float4 Position							: SV_POSITION;
	float4 SurfaceNormal					: SURFACE_NORMAL;
	float2 TexCoord							: TEXCOORD0;
	uint   MaterialIndex					: MATERIAL_INDEX;

	//Light
	float3 viewDirection					: VIEW_DIRECTION;
	float3 ToLightVector[ZA_LIGHT_COUNT]	: TO_LIGHT_VECTOR;
};

/* //////////////////////////////////////////////////////////////////////////////// */
// // Vertex Shader //
/* //////////////////////////////////////////////////////////////////////////////// */

/* ********************************************************* */
// * Buffers *
/* ********************************************************* */

cbuffer ZA_VS_MATRIX_BUFFER : register(b0)
{
	float4x4 TransformationMatrix;
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
}

cbuffer ZA_VS_SCENE_BUFFER : register(b1)
{
	float3 CameraPosition;
	float VSSceneBufferPadding;
}

cbuffer ZA_VS_LIGHT_SHADER : register(b2)
{
	//16 Bytes
	uint VSLightCount;
	float3 padding;

	//16 bytes * ZA_LIGHT_COUNT
	float4 LightPositions[ZA_LIGHT_COUNT];
}


/* //////////////////////////////////////////////////////////////////////////////// */
// // Pixel Shader //
/* //////////////////////////////////////////////////////////////////////////////// */

/* ********************************************************* */
// * Definitions *
/* ********************************************************* */

struct ZA_MATERIAL {
	float3 DiffuseReflectivity;
	float SpectralReflectivity;
};

/* ********************************************************* */
// * Buffers *
/* ********************************************************* */

cbuffer ZA_PS_LIGHT_BUFFER : register(b0)
{
	uint PSLightCount;
	float3 AmbientLight;

	float4 LightColors[ZA_LIGHT_COUNT];
}

cbuffer ZA_PS_MATERIAL_BUFFER : register(b1)
{
	ZA_MATERIAL[ZA_MATERIAL_COUNT];
}

