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