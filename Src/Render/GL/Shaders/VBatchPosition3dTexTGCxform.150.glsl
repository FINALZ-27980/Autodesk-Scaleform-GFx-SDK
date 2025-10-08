#version 150
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[96];
in vec4 pos;
in float vbatch;
out vec4 fucxadd;
out vec4 fucxmul;
out vec2 tc;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(vbatch * 1.0 + 0.0+ 0.1)]);
    

    tc.x = dot(pos, vfuniforms[int(vbatch * 4.0 + 2.0+ 0.1 + 0.0)]);
    tc.y = dot(pos, vfuniforms[int(vbatch * 4.0 + 2.0+ 0.1 + 1.0)]);
    

    fucxadd = vfuniforms[int(vbatch * 4.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(vbatch * 4.0 + 1.0+ 0.1)];
    
}
