cbuffer ConstantBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
};

struct VS_INPUT
{
    float4 pos : POSITION;
    float4 color : COLOR0;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
};

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    output.color = input.color;
    return output;
}