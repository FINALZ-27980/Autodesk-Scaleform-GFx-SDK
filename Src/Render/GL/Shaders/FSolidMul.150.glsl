#version 150
uniform vec4 cxmul;
out vec4 fcolor;
void main() { 

    fcolor = cxmul;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
