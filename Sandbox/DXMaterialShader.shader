//////////////
// TYPEDEFS //
//////////////
#define SUPPORTET_LIGHT_COUNT 8

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
	float3 toLightVector[SUPPORTET_LIGHT_COUNT] : TO_LIGHT_VECTOR;
	float3 viewDirection : VIEW_DIRECTION;
	uint material : MATERIAL;
};

////////////////
// VS GLOBALS //
////////////////
cbuffer matrices : register(b0)
{
	float4x4 ProjectionMatrix;
	float4x4 TransformationMatrix;
	float4x4 ViewMatrix;
}
cbuffer light : register(b1)
{
	uint VSLightCount;
	float3 padding1;
	
	float4 lightPosition[SUPPORTET_LIGHT_COUNT];
}
cbuffer scene : register(b2)
{
	float3 cameraPosition;
	float padding2;
}

//////////////////
// VertexShader //
//////////////////
VOut VShader(VSInput input)
{
	VOut output;

	//Position
	float4 worldPosition = mul(TransformationMatrix, input.position);
	output.position = mul(ViewMatrix, worldPosition);
	output.position = mul(ProjectionMatrix, output.position);
	
	//Normal
	output.surfaceNormal = mul(TransformationMatrix, input.normal.xyz);
	
	//Light
	for (uint i = 0; i < VSLightCount; i++)
	{
		output.toLightVector[i] = lightPosition[i].xyz - worldPosition.xyz;
	}
	

	//View direction
	output.viewDirection = worldPosition.xyz - cameraPosition;

	//Material
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
	uint PSLightCount;
	float3 padding;

	float4 ambientLightColor;
	
	float4 lightColor[SUPPORTET_LIGHT_COUNT];
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
	float3 viewDirection = normalize(input.viewDirection);
	float3 color = materials[input.material].Color.xyz;

	float3 lightDirection;
	float brightness, specular, reflection;
	float3 diffuse = ambientLightColor;
	for (uint i = 0; i < PSLightCount; i++)
	{
		lightDirection = normalize(input.toLightVector[i]);
		
		//diffuse
		brightness = max(dot(normal, lightDirection), 0.0);
		diffuse += saturate(brightness * lightColor[i].xyz);

		//specular
		reflection = normalize(reflect(lightDirection, normal));
		specular += saturate(dot(reflection, viewDirection)) * materials[input.material].Reflectivity;
	}
	//diffuse
	color *= diffuse;
	color += float3(specular, specular, specular);

	return float4(color.xyz, 1.0f);
}
