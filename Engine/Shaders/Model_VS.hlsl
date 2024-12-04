#include "Model.hlsli"

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
    
    output.position = mul(input.position, world);
    output.worldPosition = output.position;
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    
    output.uv = input.uv;
    output.normal = normalize(mul(float4(input.normal, 0.0f), world).xyz);
    
    return output;
};