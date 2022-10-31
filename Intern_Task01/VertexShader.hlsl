#include "BasicShaderHeader.hlsli"

OUTPUT BasicVS(float4 pos : POSITION, float2 uv : TEXCOORD)
{
	OUTPUT output;
	output.svpos = mul(mat, pos);
	output.uv = uv;
	return output;
}