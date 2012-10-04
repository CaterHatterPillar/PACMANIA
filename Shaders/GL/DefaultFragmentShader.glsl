#version 330

/*IN*/
in vec2 TexCoord0;

/*OUT*/
out vec4 fragColor;

uniform sampler2D sampler;

void main()
{
	vec4 tex	= texture2D(sampler, TexCoord0.xy);
	
	if(tex.a <= 0.0f)
		discard;

	fragColor = tex; 
}
