R"(#define ZAAP_SHADER_LIGHT_COUNT 4

/////////////
// GLOBALS //
/////////////
cbuffer VSMatrixBuffer : register(b0)
{
	float4x4 ProjectionMatrix;
	float4x4 TransformationMatrix;
	float4x4 ViewMatrix;
}
cbuffer VSLightBuffer : register(b1)
{
	uint VSLightCount;
	float VSPadding;

	float4 lightPositions[ZAAP_SHADER_LIGHT_COUNT];
}

//////////////
// TYPEDEFS //
//////////////
struct VSInput {
	float4 position      : POSITION;
	float4 normal        : NORMAL;
	float2 texCoords     : TEXCOORD;
};
struct VOut
{
	float4 position                               : SV_POSITION;
	float2 texCoords                              : TEXCOORD0;
	float3 surfaceNormal                          : SURFACE_NORMAL;
	float3 toLightVector[ZAAP_SHADER_LIGHT_COUNT] : TO_LIGHT_VECTOR;
};

//////////////////
// VertexShader //
//////////////////
VOut VShader(VSInput input)
{
	VOut output;

	float4 worldPosition = mul(TransformationMatrix, input.position);
	
	//output
	output.position = mul(ViewMatrix, worldPosition);
	output.position = mul(ProjectionMatrix, output.position);
	output.texCoords = input.texCoords;

	//light
	output.surfaceNormal = mul(TransformationMatrix, input.normal.xyz);
	for (uint i = 0; i < VSLightCount; i++)
	{
		output.toLightVector[i] = lightPositions[i] - worldPosition.xyz;
	}

	return output;
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/////////////
// GLOBALS //
/////////////
Texture2D texture_;
SamplerState sampler_;

cbuffer PSLightBuffer : register(b0)
{
	uint PSLightCount;
	float3 AmbientLight;
	float4 LightColors[ZAAP_SHADER_LIGHT_COUNT];
}

/////////////////
// PixelShader //
/////////////////
float4 PShader(VOut input) : SV_TARGET
{
	float3 normal = normalize(input.surfaceNormal);
	float4 color = texture_.Sample(sampler_, input.texCoords);
	
	//light
	float3 lightVector;
	float brightness;
	float3 diffuse = AmbientLight;
	for (uint i = 0; i < PSLightCount; i++)
	{
		lightVector = normalize(input.toLightVector[i]);
		brightness = max(dot(normal, lightVector), 0.0);
		diffuse += brightness * LightColors[i].xyz;
	}

	color.xyz *= clamp(diffuse, 0.0, 1.0);

	return color;
})"