#include "VS_OutPut.h"



float4 main(VS_Output input) : SV_TARGET
{
    float4 lightColor = { 1., 1., 1., 1. };
    float3 lightPos = { 10., 10., 10. };
    float3 viewPos = { 0., 0., 10. };
    
    float ambientStrength = .0;
    float4 ambient = ambientStrength * lightColor;
    
    float diffuseStrength = 1.;
    float3 lightDir = normalize(input.vertexPos - lightPos);
    float diff = max(dot(input.normal, -lightDir), 0.);
    float4 diffuse = diffuseStrength * diff * lightColor;


    float specularStrenght = 0.0;
    float3 refDir = reflect(-lightDir, input.normal);
    float3 viewDir = normalize(viewPos - input.vertexPos);
    float spec = pow(max(dot(viewDir, refDir), 0.), 32);
    float4 specular = specularStrenght * spec * lightColor;


    return (ambient + diffuse + specular) * input.color;
}