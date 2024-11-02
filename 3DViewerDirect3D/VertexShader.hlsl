#include "VS_OutPut.h"

struct VS_Input
{
    //TODO
};



VS_Output main(VS_Input input)
{
    VS_Output output;
    output.position = float4(0.0f, 0.0f, 0.0f, 1.0f);   //TODO
    output.color = float4(1.0f, 0.0f, 0.0f, 1.0f);      //TODO
    return output;
}