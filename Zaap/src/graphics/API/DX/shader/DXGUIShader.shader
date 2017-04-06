R"(
/* //////////////////////////////////////////////////////////////////////////////// */
// // Macros //
/* //////////////////////////////////////////////////////////////////////////////// */
#define TYPE_COLOR		0
#define TYPE_TEXTURE	1
#define TYPE_FONT		2

/* //////////////////////////////////////////////////////////////////////////////// */
// ///Input/Output //
/* //////////////////////////////////////////////////////////////////////////////// */
struct ZA_VS_INPUT {
	float4 Position			: POSITION;
	uint   Type				: TYPE;
	float4 TypeInfo			: TYPEINFO;
};

struct ZA_VS_OUTPUT {
	float4 Position			: SV_POSITION;
	uint   Type				: TYPE;
	float4 TypeInfo			: TYPEINFO;
};

typedef ZA_VS_OUTPUT ZA_PS_INPUT;

/* //////////////////////////////////////////////////////////////////////////////// */
// // Vertex Shader //
/* //////////////////////////////////////////////////////////////////////////////// */

/* ********************************************************* */
// * Buffers *
/* ********************************************************* */
cbuffer ZA_VS_MATRIX_BUFFER : register(b0)
{
	float4x4 TransformationMatrix;
}

/* ********************************************************* */
// * Function *
/* ********************************************************* */
ZA_VS_OUTPUT VShader(ZA_VS_INPUT input)
{
	ZA_VS_OUTPUT output;

	output.Position = mul(TransformationMatrix, input.Position);
	output.Type     = input.Type;
	output.TypeInfo = input.TypeInfo;

	return output;
}

/* //////////////////////////////////////////////////////////////////////////////// */
// // Pixel Shader //
/* //////////////////////////////////////////////////////////////////////////////// */

/* ********************************************************* */
// * Buffers *
/* ********************************************************* */
Texture2D Texture				: register(t0);
SamplerState TextureSampler		: register(s0);

Texture2D CharSheet				: register(t1);
SamplerState CharSampler		: register(s1);

cbuffer ZA_PS_COLOR_BUFFER : register(b0)
{
	float4 TextColor;
}

/* ********************************************************* */
// * Function *
/* ********************************************************* */

float4 PShader(ZA_PS_INPUT input) : SV_TARGET
{
	switch (input.Type)
	{
	case TYPE_COLOR:
		return input.TypeInfo;
	case TYPE_TEXTURE:
		return Texture.Sample(TextureSampler, input.TypeInfo.xy);
	case TYPE_FONT:
		float4 color = CharSheet.Sample(CharSampler, input.TypeInfo.xy);
		if (color.w != 0)
			return color;//.x * TextColor;
		return float4(1.0f, 1.0f, 1.0f, 1.0f);
		
	default:
		return float4(1.0f, 0.0f, 1.0f, 1.0f);
	}
})"
