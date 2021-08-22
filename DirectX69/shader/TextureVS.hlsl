cbuffer CBuffer
{
    matrix transform;
};

struct VSout
{
    float2 tex : TexCoord;
    float4 pos : SV_Position;
};

VSout main(float3 pos : Position, float2 tex : TexCoord)
{
    VSout vso;
    vso.pos = mul(float4(pos, 1.0f), transform);
    vso.tex = tex;
    return vso;
}