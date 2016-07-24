/////////////
// GLOBALS //
/////////////
Texture2D texture_;
SamplerState sampler_;

//////////////
// TYPEDEFS //
//////////////
struct VOut
{
    float4 position : SV_POSITION;
    float2 texCoords : TEXCOORD0;
};

/////////////////
// PixelShader //
/////////////////
float4 PShader(VOut input) : SV_TARGET
{
	float4 color = texture_.Sample(sampler_, input.texCoords);
    return float4(color.z, color.y, color.x, color.w);
}
