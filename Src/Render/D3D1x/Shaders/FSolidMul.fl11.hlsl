cbuffer Constants { 
float4 cxmul : packoffset(c0);
};

void main( out float4 fcolor : SV_Target0)
{
    fcolor = cxmul;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    

      fcolor = fcolor;
    
}
