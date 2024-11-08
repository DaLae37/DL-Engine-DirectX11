cbuffer CameraBuffer : register(b0)
{
    matrix view;
    matrix projection;
};

cbuffer ObjectBuffer : register(b1)
{
    matrix World;
}

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