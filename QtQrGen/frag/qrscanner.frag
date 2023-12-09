#version 440
#define PI     3.14159265
layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 0) out vec4 fragColor;

layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
    vec2 pixelStep;
    vec4 fcolor;
};
layout(binding = 1) uniform sampler2D src;

float sdOrientedBox( in vec2 p, in vec2 a, in vec2 b, float th )
{
    float l = length(b-a);
    vec2  d = (b-a)/l;
    vec2  q = (p-(a+b)*0.5);
    q = mat2(d.x,-d.y,d.y,d.x)*q;
    q = abs(q)-vec2(l,th)*0.5;
    return length(max(q,0.0)) + min(max(q.x,q.y),0.0);
}

float frame(in vec2 uv, in float width )
{
    float frameH=1.0-smoothstep(0.0,0.0,sdOrientedBox( uv, vec2(1.5,1.0)*width,
                                                       vec2(0.3,0.0+width), width));
    float frameV=1.0-smoothstep(0.0,0.0,sdOrientedBox( uv, vec2(1.0,0.5)*width,
                                                       vec2(0.0+width,0.3), width));

    return clamp(frameH+frameV,0.0,1.0);

}


void main( void)
{
    vec2 uv=qt_TexCoord0;

    float width=0.1;

    vec2 uv4=abs(fract(uv+0.5)-0.5);

    float d=frame(uv4,width);

    float b=0.008;

    d+=1.0-smoothstep(0.0,b,sdOrientedBox( uv, vec2(2.5,6.5)*width,
                                           vec2(4.5,6.5)*width, 2.0*width));

    d+=1.0-smoothstep(0.0,b,sdOrientedBox( uv, vec2(2.5,2.5)*width,
                                           vec2(3.5,2.5)*width, width));

    d+=1.0-smoothstep(0.0,b,sdOrientedBox( uv, vec2(3.5,3.5)*width,
                                           vec2(4.5,3.5)*width, width));

    d+=1.0-smoothstep(0.0,b,sdOrientedBox( uv, vec2(4.5,2.5)*width,
                                           vec2(5.5,2.5)*width, width));

    d+=1.0-smoothstep(0.0,b,sdOrientedBox( uv, vec2(5.5,3.5)*width,
                                           vec2(6.5,3.5)*width, width));

    d+=1.0-smoothstep(0.0,b,sdOrientedBox( uv, vec2(6.5,2.5)*width,
                                           vec2(7.5,2.5)*width, width));

    d+=1.0-smoothstep(0.0,b,sdOrientedBox( uv, vec2(6.5,4.5)*width,
                                           vec2(7.5,4.5)*width, width));

    d+=1.0-smoothstep(0.0,b,sdOrientedBox( uv, vec2(5.5,5.5)*width,
                                           vec2(6.5,5.5)*width, width));

    d+=1.0-smoothstep(0.0,b,sdOrientedBox( uv, vec2(6.5,6.5)*width,
                                           vec2(7.5,6.5)*width, width));

    vec4 bcolor=texture(src, uv).rgba;
    vec4 color=mix(bcolor,fcolor , d);

    fragColor = color;

}
