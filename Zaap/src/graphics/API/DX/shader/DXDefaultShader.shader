R"(
/* //////////////////////////////////////////////////////////////////////////////// */
// // Macros //
/* //////////////////////////////////////////////////////////////////////////////// */
// Macros have to be set in the loading process
#define ZA_LIGHT_COUNT    ZA_SHADER_LIGHT_COUNT
#define ZA_MATERIAL_COUNT ZA_SHADER_MATERIAL_COUNT

/* //////////////////////////////////////////////////////////////////////////////// */
// ///Input/Output //
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
	float3 ViewDirection					: VIEW_DIRECTION;
	float3 ToLightVector[ZA_LIGHT_COUNT]	: TO_LIGHT_VECTOR;
};

typedef ZA_VS_OUTPUT ZA_PS_INPUT;

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
	float3 VSLightBufferPadding;

	//16 bytes * ZA_LIGHT_COUNT
	float4 LightPositions[ZA_LIGHT_COUNT];
}

/* ********************************************************* */
// * Function *
/* ********************************************************* */

ZA_VS_OUTPUT VShader(ZA_VS_INPUT input)
{
	ZA_VS_OUTPUT output;

	// Position
	float4 worldPosition = mul(TransformationMatrix, input.Position);

	output.Position = mul(ViewMatrix, worldPosition);
	output.Position = mul(ProjectionMatrix, output.Position);
	//output.Position = mul(ProjectionMatrix, mul(ViewMatrix, worldPosition));
	
	// Normal (kys)
	output.SurfaceNormal = mul(TransformationMatrix, float4(input.Normal.xyz, 0.0));

	// TexCoord
	output.TexCoord = input.TexCoord;

	// Material
	output.MaterialIndex = input.MaterialIndex;

	// ViewDirection
	output.ViewDirection = worldPosition.xyz - CameraPosition;

	// ToLightVector
	for (uint i = 0; i < VSLightCount; i++)
	{
		output.ToLightVector[i] = LightPositions[i].xyz - worldPosition.xyz;
	}

	return output;
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

Texture2D Texture				: register(t0);
SamplerState TextureSampler		: register(s0);

cbuffer ZA_PS_LIGHT_BUFFER : register(b0)
{
	uint PSLightCount;
	float3 AmbientLight;

	float4 LightColors[ZA_LIGHT_COUNT];
}

cbuffer ZA_PS_MATERIAL_BUFFER : register(b1)
{
	ZA_MATERIAL Materials[ZA_MATERIAL_COUNT];
}

/* ********************************************************* */
// * Function *
/* ********************************************************* */

float4 PShader(ZA_PS_INPUT input)  : SV_TARGET
{

	float3 normal = normalize(input.SurfaceNormal.xyz);
	float3 viewDirection = normalize(input.ViewDirection);
	float4 color = Texture.Sample(TextureSampler, input.TexCoord);

	//lighting
	float3 lightDirection;
	// diffuse lighting 
	float  brightness; // the light efficiency for diffuse lighting (0.0 to 1.0)
	float3 diffuse = AmbientLight;
	// specular lighting
	float3 reflection; // the reflection vector of the current light.
	float  specular;
	for (uint i = 0; i < PSLightCount; i++)
	{
		lightDirection = normalize(input.ToLightVector[i]);
		
		//diffuse
		brightness = max(dot(normal, lightDirection), 0.0);
		diffuse   += brightness * LightColors[i].xyz;
		
		//specular
		reflection = normalize(reflect(lightDirection, normal));
		specular  += saturate(dot(reflection, input.ViewDirection)) * Materials[input.MaterialIndex].SpectralReflectivity;
	}

	color.xyz *= saturate(diffuse) * Materials[input.MaterialIndex].DiffuseReflectivity;
	color.xyz += float3(specular, specular, specular);

	return color;
	//return Texture.Sample(TextureSampler, input.TexCoord);
	//return float4(1.0, 1.0, 1.0, 1.0);
})"
