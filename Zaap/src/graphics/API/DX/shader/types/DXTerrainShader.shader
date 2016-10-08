R"(//////////////////////
// Type definitions //
//////////////////////
#define ZAAP_SHADER_LIGHT_COUNT 4

struct VS_IN
{
	float4 Position			: POSITION;
	float4 Normal			: NORMAL;
	float3 TexMapColor		: TEXMAPCOLOR;
	float2 TexCoord			: TEXCOORD;
};
struct VS_OUT
{
	float4 Position			: SV_POSITION;
	float3 TexMapColor		: TEXMAPCOLOR;
	float2 TexCoord			: TEXCOORD;
	float4 SurfaceNormal	: SURFACE_NORMAL;
	float3 ToLightVector[ZAAP_SHADER_LIGHT_COUNT]	: TO_LIGHT_VECTOR;
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
	float4 LightPosition[ZAAP_SHADER_LIGHT_COUNT];
}

///////////////////
// Vertex Shader //
///////////////////
VS_OUT VShader(VS_IN input)
{
	VS_OUT output;

	//Position
	float4 worldPosition = input.Position;

	output.Position = mul(ViewMatrix, worldPosition);
	output.Position = mul(ProjectionMatrix, output.Position);

	//Texture Coord
	output.TexMapColor = input.TexMapColor;
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
//Textures
Texture2D defaultTex			: register(t0);
SamplerState defaultTexSampler	: register(s0);

Texture2D tex0					: register(t1);
SamplerState texSampler0		: register(s1);

Texture2D tex1					: register(t2);
SamplerState texSampler1		: register(s2);

Texture2D tex2					: register(t3);
SamplerState texSampler2		: register(s3);


cbuffer PSLightBuffer : register(b0)
{
	uint PSLightCount;
	float3 PSLightPadding;
	float4 LightColor[ZAAP_SHADER_LIGHT_COUNT];
}

//////////////////
// Pixel Shader //
//////////////////
float4 PShader(VS_OUT input) : SV_TARGET
{
	float3 texMapColor = input.TexMapColor;
	float3 normal = normalize(input.SurfaceNormal.xyz);
	
	float defaultColorFactor = (1.0 - texMapColor.x - texMapColor.y - texMapColor.z);
	float4 color = defaultTex.Sample(defaultTexSampler, input.TexCoord) * max(defaultColorFactor, 0.0);
	color += tex0.Sample(texSampler0, input.TexCoord) * texMapColor.x;
	color += tex1.Sample(texSampler1, input.TexCoord) * texMapColor.y;
	color += tex2.Sample(texSampler2, input.TexCoord) * texMapColor.z;
	
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

	//return float4(texMapColor, 1.0);
	return float4(color.xyz, 1.0);
	//return float4(1.0, 1.0, 1.0, 1.0);
	//return float4(normal, 1.0);

})"