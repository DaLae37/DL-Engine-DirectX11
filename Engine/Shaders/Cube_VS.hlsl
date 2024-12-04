#include "Polygon.hlsli"

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
    
    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    output.color = input.color;
    
    return output;
}