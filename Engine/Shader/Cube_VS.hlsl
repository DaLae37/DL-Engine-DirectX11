cbuffer CameraBuffer : register(b0)
{
    matrix view;
    matrix projection;
};

cbuffer ObjectBuffer : register(b1)
{
    matrix world;
}

struct VS_INPUT
{
    float4 pos : POSITION;
    float4 color : COLOR;
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