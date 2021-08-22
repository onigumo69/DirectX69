cbuffer CBuffer
{
    matrix transform;
};

struct VSout
{
    float4 color : Color;
    float4 pos : SV_Position;
};

VSout main(float3 pos : Position, float4 color : Color)
{
    VSout vso;
    vso.pos = mul(float4(pos, 1.0f), transform);
    vso.color = color;
    return vso;
}