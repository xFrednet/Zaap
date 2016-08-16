//////////////////////
// Type definitions //
//////////////////////
struct VS_IN
{
	float4 Position			: POSITION;
	float4 Normal			: NORMAL;
	float2 TexMapCoord		: TEXMAPCOORD;
	float2 TexCoord			: TEXCOORD;
};
struct VS_OUT
{
	float4 Position			: SV_POSITION;
	float2 TexMapCoord		: TEXMAPCOORD;
	float2 TexCoord			: TEXCOORD;
	float4 SurfaceNormal	: SURFACE_NORMAL;
	float3 ToLightVector	: TO_LIGHT_VECTOR;
};

/////////////
// Globals //
/////////////
#define SUPPORTET_LIGHT_COUNT 8

cbuffer MatrixBuffer : register(b0)
{
	float4x4 ProjectionMatrix;
	float4x4 TransformationMatrix;
	float4x4 ViewMatrix;
};
cbuffer VSLightBuffer : register(b1)
{
	uint VSLightCount;
	float3 VSLightPadding;
	float4 LightPosition[SUPPORTET_LIGHT_COUNT];
}

///////////////////
// Vertex Shader //
///////////////////
VS_OUT VShader(VS_IN input)
{
	VS_OUT output;

	//Position
	float4 worldPosition = mul(TransformationMatrix, input.Position);
	output.Position = mul(ViewMatrix, worldPosition);
	output.Position = mul(ProjectionMatrix, output.Position);

	//Texture Coord
	output.TexMapCoord = input.TexMapCoord;
	output.TexCoord = input.TexCoord;

	//Surface Normal
	output.SurfaceNormal = mul(TransformationMatrix, input.Normal.xyz);

	//To Light Vector
	output.ToLightVector = LightPosition[0].xyz - worldPosition.xyz;

	return output;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/////////////
// Globals //
/////////////
//TextureMap
Texture2D texMap			: register(t0);
SamplerState texMapSampler	: register(s0);

//Textures
Texture2D defaultTex			: register(t1);
SamplerState defaultTexSampler	: register(s1);

Texture2D tex0					: register(t2);
SamplerState texSampler0		: register(s2);

Texture2D tex1					: register(t3);
SamplerState texSampler1		: register(s3);

Texture2D tex2					: register(t4);
SamplerState texSampler2		: register(s4);


cbuffer PSLightBuffer : register(b0)
{
	uint PSLightCount;
	float3 PSLightPadding;
	float4 LightColor[SUPPORTET_LIGHT_COUNT];
}

//////////////////
// Pixel Shader //
//////////////////
float4 PShader(VS_OUT input) : SV_TARGET
{
	float3 normal = normalize(input.SurfaceNormal.xyz);
	float4 color = texMap.Sample(texMapSampler, input.TexMapCoord);
	
	float3 lightVector = normalize(input.ToLightVector);
	float t = dot(normal, lightVector);
	float brightness = saturate(max(t, 0.0));

	float3 diffuse = brightness * LightColor[0];

	color.xyz *= diffuse;

	return float4(color.xyz, 1.0f);
}