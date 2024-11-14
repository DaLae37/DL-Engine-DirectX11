cbuffer CameraBuffer : register(b0)
{
    matrix view;
    matrix projection;
};

cbuffer ObjectBuffer : register(b1)
{
    matrix world;
};

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