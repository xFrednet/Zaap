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
cbuffer scene : register(b2)
{
	float3 cameraPosition;
	float padding;
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
	float3 viewDirection : VIEW_DIRECTION;
	uint material : MATERIAL;
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
	output.toLightVector = lightPosition.xyz - worldPosition.xyz;

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
	float3 lightDirection = normalize(input.toLightVector);
	
	float3 reflection = normalize(reflect(lightDirection, normal));
	float sp = saturate(dot(reflection, normalize(input.viewDirection)));
	//float sp = saturate(dot(reflection, float3(1.0, 0.0, 0.0)));
	float specular = sp * materials[input.material].Reflectivity;
	//diffuse
	float brightness = max(dot(normal, lightDirection), 0.1);
	float3 diffuse = brightness * lightColor.xyz;
	float3 color = materials[input.material].Color.xyz * diffuse;

	return float4(color.xyz + specular, 1.0f);
}
