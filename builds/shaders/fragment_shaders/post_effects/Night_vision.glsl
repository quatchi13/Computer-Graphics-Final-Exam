#version 430

// Modified from https://tobiasbu.wordpress.com/2016/01/16/opengl-night-vision-shader/
layout (location = 0) in vec2 inUV;
layout (location = 0) out vec3 outColor;
 
uniform layout (binding = 0) sampler2D scene;
 
void main()
{ 

	vec3 normal = texture(scene, inUV).rgb * 1;      
   
	vec3 NightVisionColor = vec3(0,1,0);
	outColor = normal * NightVisionColor;
}
