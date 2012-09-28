#version 330

/*IN*/
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 Tex;

/*OUT*/
out vec4 Color;

/*UNIFORMS*/
uniform mat4 wvp;

void main()
{
	gl_Position = wvp * vec4(Position, 1.0f);	
	Color = vec4(clamp(Position, 0.0, 1.0), 1.0);
}
