cbuffer Constants { 
float4 cxmul : packoffset(c0);
};

void main( out float4 fcolor : SV_Target0)
{
    fcolor = cxmul;
    

    fcolor.rgb = float3(fcolor.a, fcolor.a, fcolor.a);
    

      fcolor = fcolor;
    
}
