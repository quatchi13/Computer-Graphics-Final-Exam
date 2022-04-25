#version 430

// Modified from: https://gamedev.stackexchange.com/questions/111017/pixelation-shader-explanation

layout (location = 0) in vec2 inUV;
layout (location = 0) out vec3 outColor;

uniform layout (binding = 0) sampler2D normals;

uniform float u_Scale;

uniform float u_Amount;

void main()
{
    float dx = u_Scale * (1.0 / u_Amount);
    float dy = u_Scale * (1.0 / u_Amount);
    vec2 coord = vec2(dx *floor(inUV.x/dx), dy *floor(inUV.y / dy));
    outColor = texture(normals, coord).rgb;
}

