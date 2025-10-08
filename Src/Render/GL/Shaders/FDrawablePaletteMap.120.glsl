#version 120
uniform sampler2D srctex;
uniform sampler2D tex;
varying vec2 tc;
void main() { 

    vec4 fchannels = texture2D(tex, tc);
    gl_FragColor  = texture2D(srctex, vec2(fchannels.r, 0.125));
    gl_FragColor += texture2D(srctex, vec2(fchannels.g, 0.375));
    gl_FragColor += texture2D(srctex, vec2(fchannels.b, 0.625));
    gl_FragColor += texture2D(srctex, vec2(fchannels.a, 0.875));
    
}
