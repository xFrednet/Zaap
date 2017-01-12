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
	float alpha = charSheet.Sample(charSampler, input.TexCoord).w;
	
	//returns nothing if the color is #ff000000
	return float4(textColor.xyz, textColor.w * (alpha));
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
})"