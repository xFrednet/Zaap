#define ZAAP_SHADER_LIGHT_COUNT 4
#define ZAAP_SHADER_MATERIAL_COUNT 8
////////////////
// VS GLOBALS //
////////////////
cbuffer VSMatrixBuffer : register(b0)
{
	float4x4 ProjectionMatrix;
	float4x4 TransformationMatrix;
	float4x4 ViewMatrix;
}
cbuffer VSLightBuffer : register(b1)
{
	uint VSLightCount;
	float3 VSLightPadding;
	
	float4 lightPosition[ZAAP_SHADER_LIGHT_COUNT];
}
cbuffer VSSceneBuffer : register(b2)
{
	float3 cameraPosition;
	float VSScenePadding;
}

//////////////
// TYPEDEFS //
//////////////
struct VSInput
{
	float4 position : POSITION;
	float4 normal   : NORMAL;
	uint material   : MATERIAL;
};
struct VOut
{
	float4 position            : SV_POSITION;
	float3 surfaceNormal       : SURFACE_NORMAL;
	uint material              : MATERIAL;
	float3 viewDirection       : VIEW_DIRECTION;
	float3 toLightVector[ZAAP_SHADER_LIGHT_COUNT] : TO_LIGHT_VECTOR;
};


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
	
	//Material
	output.material = input.material;
	
	//View direction
	output.viewDirection = worldPosition.xyz - cameraPosition;
	
	//Light
	for (uint i = 0; i < VSLightCount; i++)
	{
		output.toLightVector[i] = lightPosition[i].xyz - worldPosition.xyz;
	}

	return output;
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/////////////
// GLOBALS //
/////////////
cbuffer PSLightBuffer : register(b0)
{
	uint PSLightCount;
	float3 AmbientLight;
	
	float4 LightColors[ZAAP_SHADER_LIGHT_COUNT];
}
struct PSMaterial
{
	float3 Color;
	float Reflectivity;
};
cbuffer PSMaterialBuffer : register(b1)
{
	PSMaterial materials[ZAAP_SHADER_MATERIAL_COUNT];
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
	float3 diffuse = AmbientLight;
	for (uint i = 0; i < PSLightCount; i++)
	{
		lightDirection = normalize(input.toLightVector[i]);
		
		//diffuse
		brightness = max(dot(normal, lightDirection), 0.0);
		diffuse += saturate(brightness * LightColors[i].xyz);

		//specular
		reflection = normalize(reflect(lightDirection, normal));
		specular += saturate(dot(reflection, viewDirection)) * materials[input.material].Reflectivity;
	}
	//diffuse
	color *= clamp(diffuse, 0.0, 1.0);
	color += float3(specular, specular, specular);

	return float4(color.xyz, 1.0);
}
