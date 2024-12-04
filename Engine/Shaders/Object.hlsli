cbuffer CameraBuffer : register(b0)
{
    matrix view;
    matrix projection;
    float4 cameraPosition;
};

cbuffer LightBuffer : register(b1)
{ 
    float4 diffuseColor;
    float4 specularColor;
    float4 ambientColor;
    float4 lightDirection;
};

cbuffer ObjectBuffer : register(b2)
{
    matrix world;
};