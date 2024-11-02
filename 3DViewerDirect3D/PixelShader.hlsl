#include "VS_OutPut.h"

float4 main(VS_Output input) : SV_TARGET
{
    return input.color;
}