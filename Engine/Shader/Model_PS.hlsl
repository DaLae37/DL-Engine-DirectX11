#include "Model.hlsli"

Texture2D modelTexture : register(t0);
SamplerState modelSampler : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    return modelTexture.Sample(modelSampler, input.uv);
}