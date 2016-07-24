/////////////
// GLOBALS //
/////////////
cbuffer matrices : register(b0)
{
	float4x4 ProjectionMatrix;
	float4x4 TransformationMatrix;
	float4x4 ViewMatrix;
}
cbuffer light : register(b1)
{
	float3 lightPosition;
	float filler;
}

//////////////
// TYPEDEFS //
//////////////
struct VSInput {
	float4 position : POSITION;
	float2 texCoords : TEXCOORD;
	float4 normal : NORMAL;
};
struct VOut
{
	float4 position : SV_POSITION;
	float2 texCoords : TEXCOORD0;
	float3 surfaceNormal : SURFACE_NORMAL;
	float3 toLightVector : TO_LIGHT_VECTOR;
};

//////////////////
// VertexShader //
//////////////////
VOut VShader(VSInput input)
{
	VOut output;

	float4 worldPosition = mul(TransformationMatrix, input.position);

	output.position = mul(ViewMatrix, worldPosition);
	output.position = mul(ProjectionMatrix, output.position);
	output.texCoords = input.texCoords;

	output.surfaceNormal = mul(TransformationMatrix, input.normal.xyz);
	output.toLightVector = lightPosition - worldPosition.xyz;

	return output;
}

/////////////
// GLOBALS //
/////////////
Texture2D texture_;
SamplerState sampler_;

cbuffer lightColor : register(b0)
{
	float4 lightColor;
}

/////////////////
// PixelShader //
/////////////////
float4 PShader(VOut input) : SV_TARGET
{
	float3 normal = normalize(input.surfaceNormal);
	float3 lightVector = normalize(input.toLightVector);
	
	float brightness = max(dot(normal, lightVector), 0.1);
	float3 diffuse = brightness * lightColor.xyz;
	float4 color = texture_.Sample(sampler_, input.texCoords);
	
	return float4(color.xyz * diffuse, color.w);
}