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
	float4 lightPosition;
}

//////////////
// TYPEDEFS //
//////////////
struct VSInput
{
	float4 position : POSITION;
	float4 normal : NORMAL;
	uint material : MATERIAL;
};
struct VOut
{
	float4 position : SV_POSITION;
	float3 surfaceNormal : SURFACE_NORMAL;
	float3 toLightVector : TO_LIGHT_VECTOR;
	uint material : MATERIAL;
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
	
	output.surfaceNormal = mul(TransformationMatrix, input.normal.xyz);
	output.toLightVector = lightPosition.xyz - worldPosition.xyz;

	output.material = input.material;

	return output;
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/////////////
// GLOBALS //
/////////////
struct Material
{
	float3 Color;
	float Reflectivity;
};

cbuffer lightColor : register(b0)
{
	float4 lightColor;
}
cbuffer materials : register(b1)
{
	Material materials[8];
};

/////////////////
// PixelShader //
/////////////////
float4 PShader(VOut input) : SV_TARGET
{
	float3 normal = normalize(input.surfaceNormal);
	float3 lightVector = normalize(input.toLightVector);

	float brightness = max(dot(normal, lightVector), 0.1);
	float3 diffuse = brightness * lightColor.xyz;
	float4 color = float4(materials[input.material].Color.xyz, 1.0f);

	return float4(color.xyz * diffuse, brightness);
}
