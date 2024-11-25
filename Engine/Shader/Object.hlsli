cbuffer CameraBuffer : register(b0)
{
    matrix view;
    matrix projection;
    float4 cameraPosition;
};

cbuffer ObjectBuffer : register(b1)
{
    matrix world;
};

cbuffer LightBuffer : register(b2)
{
    float4 lightPosition;
}