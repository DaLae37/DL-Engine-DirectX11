// Vertex Shader
struct VS_INPUT
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output;
    output.pos = float4(input.pos, 1.0f);
    output.tex = input.tex;
    return output;
}

// Pixel Shader
Texture2D texture : register(t0);
SamplerState samplerState : register(s0);

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
    return texture.Sample(samplerState, input.tex);
}