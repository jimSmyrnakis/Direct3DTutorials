

float4 main(float4 color : COLOR0) : SV_TARGET
{
    return float4(color.rgb, 1);
}