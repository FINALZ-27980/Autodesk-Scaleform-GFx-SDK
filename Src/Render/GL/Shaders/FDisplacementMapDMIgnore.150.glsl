#version 150
uniform vec4 compx;
uniform vec4 compy;
uniform vec4 mapScale;
uniform sampler2D maptex;
uniform vec2 scale;
uniform sampler2D tex;
in vec2 tc0;
out vec4 fcolor;
void main() { 

    vec2 mapTC = tc0*mapScale.xy - mapScale.zw;
    float mapInBoundsLow  = dot(step(mapTC, vec2(0.0,0)), vec2(1.0,1));
    float mapInBoundsHigh = dot(step(vec2(1.0,1), mapTC), vec2(1.0,1));
    float mapInBounds = 1.0 - clamp(mapInBoundsLow + mapInBoundsHigh, 0.0, 1.0);
    fcolor = texture(maptex,mapTC) * mapInBounds + vec4(0.5,0.5,0.5,0.5) * (1.0-mapInBounds);

    vec2 tc1;
    vec2 componentChannel;
    componentChannel.x = dot(vec4(1.0,1,1.0,1), compx * fcolor);
    componentChannel.y = dot(vec4(1.0,1,1.0,1), compy * fcolor);
    tc1 = tc0 + (componentChannel - 0.5) * scale;
    fcolor = texture(tex, tc1);
    

    float srcInBoundsLow  = dot(step(tc1, vec2(0.0,0)), vec2(1.0,1));
    float srcInBoundsHigh = dot(step(vec2(1.0,1), tc1), vec2(1.0,1));
    float srcInBounds     = 1.0 - clamp(srcInBoundsLow + srcInBoundsHigh, 0.0, 1.0);
    fcolor = (fcolor * srcInBounds) + texture(tex, tc0) * (1.0-srcInBounds);
    

      fcolor = fcolor;
    
}
