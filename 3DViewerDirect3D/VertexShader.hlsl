#include "VS_OutPut.h"

struct VS_Input
{
    float3 pos : POS;
    float4 color : COL;
    float3 nor : NOR;
};

cbuffer CBuf : register(b0)
{
    matrix modelMatrix;
};

VS_Output main(VS_Input input)
{
    VS_Output output;
    output.position = mul(modelMatrix, float4(input.pos, 1.0f));
    output.color = input.color;
    output.vertexPos = mul(modelMatrix, float4(input.pos, 1.0f));
    output.normal = mul(modelMatrix, float4(input.nor, 1.0f)).xyz;
    return output;
}