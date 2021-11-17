#version 430 core
in vec3 fs_color;
out vec4 outColor; 
	
uniform vec3 tint;

void main()
{
    outColor = vec4(fs_color * tint, 1.0);
}