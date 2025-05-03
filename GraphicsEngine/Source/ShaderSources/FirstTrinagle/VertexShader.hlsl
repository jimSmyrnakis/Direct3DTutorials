float4 main( float3 pos : POSITION1 ) : SV_POSITION
{
    return float4(pos, 1.0);
}