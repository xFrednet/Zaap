/////////////
// GLOBALS //
/////////////
cbuffer matrices : register(b0)
{
	float4x4 ProjectionMatrix;
	float4x4 TransformationMatrix;
	float4x4 ViewMatrix;
}

//////////////
// TYPEDEFS //
//////////////
struct VSInput {
	float4 position : POSITION;
	float2 texCoords : TEXCOORD;
	float4 normals : NORMAL;
};
struct VOut
{
	float4 position : SV_POSITION;
	float2 texCoords : TEXCOORD0;
};

//////////////////
// VertexShader //
//////////////////
VOut VShader(VSInput input)
{
	VOut output;

	output.position = mul(TransformationMatrix, input.position);
	output.position = mul(ViewMatrix, output.position);
	output.position = mul(ProjectionMatrix, output.position);
	output.texCoords = input.texCoords;

	return output;
}