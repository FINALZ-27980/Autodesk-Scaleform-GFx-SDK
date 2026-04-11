#version 150
uniform sampler2D tex[2];
in vec2 tc0;
in vec2 tc1;
out vec4 fcolor;
void main() { 

    vec4 fcolor0 = texture(tex[int(0.0)], tc0);
    vec4 fcolor1 = texture(tex[int(1.0)], tc1);

    vec4 diff = fcolor0 - fcolor1;
    vec4 oneValue = vec4(1.0/255.0, 1.0/255.0, 1.0/255.0, 1.0/255.0 );
    vec4 ltZero = (sign(diff)+vec4(1.0,1,1.0,1))*-0.25;
    vec4 partDiff = oneValue * (sign(ltZero)+vec4(1.0,1,1.0,1));
    vec4 wrapDiff = fract(diff + vec4(1.0,1,1.0,1)) + partDiff;
    float rgbdiff = sign(dot(wrapDiff.rgb, vec3(1.0,1,1.0)));
    fcolor = mix( vec4(1.0,1,1.0, wrapDiff.a), vec4(wrapDiff.rgb, 1.0), rgbdiff );
    
}
