


struct Interpolators
{
    float4 color : COLOR0;
    float4 position : SV_POSITION;
};

cbuffer cbuf
{
   row_major matrix MVP_Matrix;
};

Interpolators main(float2 pos : POSITION , float3 col : COLOR )
{
    Interpolators o;
    o.position = mul( float4(pos, 1, 1), MVP_Matrix);
    o.color = float4(col, 1);
    return o;
}