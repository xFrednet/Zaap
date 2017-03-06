/* //////////////////////////////////////////////////////////////////////////////// */
// // Macros //
/* //////////////////////////////////////////////////////////////////////////////// */
#define TYPE_COLOR		0
#define TYPE_TEXTURE	1

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

	output.Position = TransformationMatrix * input.Position;
	output.Type     = input.Type;
	output.TypeInfo = input.TypeInfo;

	return output;
}

/* //////////////////////////////////////////////////////////////////////////////// */
// // Pixel Shader //
/* //////////////////////////////////////////////////////////////////////////////// */

Texture2D Texture				: register(t0);
SamplerState TextureSampler		: register(s0);

/* ********************************************************* */
// * Function *
/* ********************************************************* */

float4 PShader(ZA_PS_INPUT input) : SV_TARGET
{
	switch (input.Type)
	{
	case TYPE_COLOR:
		return info.TypeInfo;
	case TYPE_TEXTURE:
		return Texture.Sample(TextureSampler, input.TypeInfo.xy);
	default:
		return float(1.0f, 0.0f, 1.0f, 1.0f);
	}
}
