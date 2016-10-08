R"(/////////////
// GLOBALS //
/////////////
cbuffer matrices : register(b0)
{
	float4x4 TransformationMatrix;
}

//////////////
// TYPEDEFS //
//////////////
struct VSInput {
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORD;
};
struct VSOut {
	float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD0;
};

///////////////////
// VertexShadert //
///////////////////
VSOut VShader(VSInput input)
{
	VSOut output;

	output.Position = mul(TransformationMatrix, input.Position);
	output.TexCoord = input.TexCoord;

	return output;
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/////////////
// GLOBALS //
/////////////
Texture2D charSheet;
SamplerState charSampler;

cbuffer ColorBuffer : register(b0)
{
	float4 textColor;
}
/////////////////
// PixelShader //
/////////////////
float4 PShader(VSOut input) : SV_TARGET
{
	float4 color = charSheet.Sample(charSampler, input.TexCoord);
	
	//return float4(0.0, 0.0, 0.0, 1.0);
	//returns nothing if the color is #ff000000
	if (color.x == 0.0f && color.x == 0.0f && color.z == 0.0f) {
		return float4(0.0, 0.0, 0.0, 0.0);
	}
	return color * textColor;
	
	
})"