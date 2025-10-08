#version 150
uniform vec4 vfuniforms[96];
in vec2 atc;
in vec4 pos;
in float vbatch;
out vec4 fucxadd;
out vec4 fucxmul;
out vec2 tc;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(vbatch * 4.0 + 2.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(vbatch * 4.0 + 2.0+ 0.1 + 1.0)]);
    

      tc = atc;
    

    fucxadd = vfuniforms[int(vbatch * 4.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(vbatch * 4.0 + 1.0+ 0.1)];
    
}
