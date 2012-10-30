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

struct SurfaceInfo
{
	vec3 pos;
	vec3 normal;
	vec4 diffuse;
	vec4 specular;
};

vec3 pointLight(SurfaceInfo surface, Light light, vec3 eyePos)
{
	vec3 litColor = vec3(0.0f, 0.0f, 0.0f);
	vec3 lightVec = light.pos - surface.pos;
	
	float d = length(lightVec);
	if(d > light.range)
		return vec3(0.0f, 0.0f, 0.0f); //Fix this!!!!!!!
		
	lightVec /= d;
	litColor += (surface.diffuse * light.ambient).xyz;
	
	float diffuseFactor = dot(lightVec, surface.normal);
	if(diffuseFactor > 0.0f)
	{
		float	specPower		= max(surface.specular.a, 1.0f);
		vec3	toEye			= normalize(eyePos - surface.pos);
		vec3	R				= reflect(-lightVec, surface.normal);
		float	specFactor		= pow(max(dot(R, toEye), 0.0f), specPower);
		
		litColor += diffuseFactor * (surface.diffuse * light.diffuse).xyz;
		litColor += specFactor * (surface.specular  * light.specular).xyz;
	}

	return litColor / dot(light.att, vec3(1.0f, d, d*d));
}

vec3 spotLight(SurfaceInfo surface, Light light, vec3 eyePos)
{
	vec3 litColor = pointLight(surface, light, eyePos);
	vec3 lightVec = normalize(light.pos - surface.pos);
	
	float s = pow(max(dot(-lightVec, light.dir), 0.0f), light.spotPow);
	return litColor * s;
}

/*CB*/
layout(std140) uniform PerFrame
{
	//Light	lights[10];
	
	vec3 camPos;

	Light light0;
	Light light1;
	Light light2;
	Light light3;
	Light light4;
	Light light5;
	Light light6;
	Light light7;
	Light light8;
	Light light9;
};

/*IN*/
in vec3 Normal0;
in vec2 TexCoord0;
in vec3 Pos0;

/*OUT*/
out vec4 gl_FragColor;

uniform sampler2D sampler;

void main()
{
	vec4 albedo = texture2D(sampler, TexCoord0.xy);

	vec4 ambient	= vec4(0.1f,	0.1f,	0.1f,	1.0f);
	vec4 diffuse	= vec4(1.0f,	1.0f,	1.0f,	1.0f);
	vec4 specular	= vec4(0.25f,	0.25f,	0.25f,	0.0f);
	specular.a *= 256.0f;
	
	vec3 normalW = normalize(Normal0);
	SurfaceInfo surface;
	surface.pos			= Pos0;
	surface.normal		= Normal0;
	surface.diffuse		= diffuse;
	surface.specular	= specular;

	vec3 litColor = vec3(0.0f, 0.0f, 0.0f);
	
	litColor += spotLight(surface, light0, camPos);
	litColor += spotLight(surface, light1, camPos);
	litColor += spotLight(surface, light2, camPos);
	litColor += spotLight(surface, light3, camPos);
	litColor += spotLight(surface, light4, camPos);
	litColor += spotLight(surface, light5, camPos);
	litColor += spotLight(surface, light6, camPos);
	litColor += spotLight(surface, light7, camPos);
	litColor += spotLight(surface, light8, camPos);
	litColor += spotLight(surface, light9, camPos);

	litColor += ambient.xyz;

	if(albedo.a <= 0.0f)
		discard;

	gl_FragColor = albedo * vec4(litColor, 1.0f);
}
