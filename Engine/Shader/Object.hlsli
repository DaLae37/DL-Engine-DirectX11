cbuffer CameraBuffer : register(b0)
{
    matrix view;
    matrix projection;
};

cbuffer ObjectBuffer : register(b1)
{
    matrix world;
};