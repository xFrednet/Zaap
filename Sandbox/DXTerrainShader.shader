//////////////////////
// Type definitions //
//////////////////////
#define SUPPORTET_LIGHT_COUNT 8

struct VS_IN
{
	float4 Position			: POSITION;
	float4 Normal			: NORMAL;
	float2 BlendMapCoord	: BLENDMAPCOORD;
	float2 TexCoord			: TEXCOORD;
};
struct VS_OUT
{
	float4 Position			: SV_POSITION;
	float2 BlendMapCoord	: BLENDMAPCOORD;
	float2 TexCoord			: TEXCOORD;
	float4 SurfaceNormal	: SURFACE_NORMAL;
	float3 ToLightVector[SUPPORTET_LIGHT_COUNT]	: TO_LIGHT_VECTOR;
};

/////////////
// Globals //
/////////////
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
	output.BlendMapCoord = input.BlendMapCoord;
	output.TexCoord = input.TexCoord;

	//Surface Normal
	output.SurfaceNormal = mul(TransformationMatrix, input.Normal.xyz);

	//To Light Vector
	for (uint i = 0; i < VSLightCount; i++)
		output.ToLightVector[i] = LightPosition[i].xyz - worldPosition.xyz;

	return output;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/////////////
// Globals //
/////////////
//TextureMap
Texture2D blendMap				: register(t0);
SamplerState blendMapSampler	: register(s0);

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
	float4 blendMapColor = blendMap.Sample(blendMapSampler, input.BlendMapCoord);
	float3 normal = normalize(input.SurfaceNormal.xyz);
	
	float defaultColorFactor = (1.0 - blendMapColor.x - blendMapColor.y - blendMapColor.z);
	float4 color = defaultTex.Sample(defaultTexSampler, input.TexCoord) * max(defaultColorFactor, 0.0);
	color += tex0.Sample(texSampler0, input.TexCoord) * blendMapColor.x;
	color += tex1.Sample(texSampler1, input.TexCoord) * blendMapColor.y;
	color += tex2.Sample(texSampler2, input.TexCoord) * blendMapColor.z;
	
	//Light
	float3 lightVector;
	float brightness;
	float3 diffuse = float3(0.0, 0.0, 0.0);
	for (uint i = 0; i < PSLightCount; i++)
	{
		lightVector = normalize(input.ToLightVector[i]);
		brightness = saturate(max(dot(normal, lightVector), 0.0));
		diffuse += brightness * LightColor[i];
	}

	color.xyz *= diffuse;

	return float4(color.xyz, 1.0);
}