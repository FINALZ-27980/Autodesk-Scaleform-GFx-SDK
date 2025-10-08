#version 150
uniform vec4 vfuniforms[96];
in vec4 afactor;
in vec4 pos;
out vec4 factor;
out vec2 tc;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(afactor.b*255.01 * 4.0 + 0.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(afactor.b*255.01 * 4.0 + 0.0+ 0.1 + 1.0)]);
    

    tc.x = dot(pos, vfuniforms[int(afactor.b*255.01 * 4.0 + 2.0+ 0.1 + 0.0)]);
    tc.y = dot(pos, vfuniforms[int(afactor.b*255.01 * 4.0 + 2.0+ 0.1 + 1.0)]);
    

      factor = afactor;
    
}
