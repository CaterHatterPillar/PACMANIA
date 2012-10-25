#version 330

/*IN*/
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 Tex;

/*OUT*/
out vec4 gl_Position;
out vec3 Normal0;
out vec2 TexCoord0;
out vec3 Pos0;

/*UNIFORMS*/
uniform mat4 wvp;
uniform mat4 world;

void main()
{
	gl_Position	= wvp * vec4(Position, 1.0f);	
	Normal0		= (world * vec4(Normal, 0.0f)).xyz;
	TexCoord0	= Tex;
	Pos0		= (world * vec4(Position, 1.0f)).xyz;
}
