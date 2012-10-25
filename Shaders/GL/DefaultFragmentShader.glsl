#version 330

struct Light
{
	vec3	pos;
	float	spotPow;
	vec3	dir;
	float	range;
	vec4	ambient;
	vec4	diffuse;
	vec4	specular;
	vec3	att;
	float	pad1;
};

/*CB*/
layout(std140) uniform PerFrame
{
	Light lights[10];
};

/*IN*/
in vec2 TexCoord0;

/*OUT*/
out vec4 gl_FragColor;

uniform sampler2D sampler;

void main()
{
	vec4 tex	= texture2D(sampler, TexCoord0.xy);
	
	if(tex.a <= 0.0f)
		discard;

	gl_FragColor = lights[7].diffuse; //tex
}
