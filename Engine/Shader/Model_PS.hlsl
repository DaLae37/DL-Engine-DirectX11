#include "Model.hlsli"

Texture2D modelTexture : register(t0);
SamplerState modelSampler : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    // Diffuse
    float3 normalizeNormal = normalize(input.normal);
    float3 normalizeLightDirection = normalize(-lightDirection.xyz);
    float NdotL = max(dot(normalizeNormal, normalizeLightDirection), 0.0f);
    float4 diffuse = diffuseColor * NdotL;

    // Specular
    float3 viewVector = normalize((cameraPosition - input.worldPosition).xyz);
    float3 reflectVector = reflect(-normalizeLightDirection, normalizeNormal);
    float specularFactor = max(dot(viewVector, reflectVector), 0.0f);
    float4 specular = specularColor * specularFactor;

    // Ambient
    float4 ambient = ambientColor;

    float4 color = modelTexture.Sample(modelSampler, input.uv);
    return float4(saturate((diffuse + specular + ambient) * color.rgb), color.a);
}