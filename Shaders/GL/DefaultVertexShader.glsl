#version 330

/*IN*/
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 Tex;

/*OUT*/
out vec4 gl_Position;
out vec2 TexCoord0;

/*UNIFORMS*/
uniform mat4 wvp;

void main()
{
	gl_Position = wvp * vec4(Position, 1.0f);	
	TexCoord0 = Tex;
}
