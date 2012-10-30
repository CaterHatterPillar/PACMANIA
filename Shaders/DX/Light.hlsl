
struct Light
{
	float3 pos;
	float spotPow;
	float3 dir;
	float range;
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 att;
	float pad1;
};

struct SurfaceInfo
{
	float3 pos;
	float3 normal;
	float4 diffuse;
	float4 specular;
};

float3 pointLight(SurfaceInfo surface, Light light, float3 eyePos)
{
	float3 litColor = float3(0.0f, 0.0f, 0.0f);
	
	float3 lightVec = light.pos - surface.pos;
	
	float d = length(lightVec);
	if(d > light.range)
		return float3(0.0f, 0.0f, 0.0f); //Fix this!!!!!!!
		
	lightVec /= d;
	
	litColor += surface.diffuse * light.ambient;
	
	float diffuseFactor = dot(lightVec, surface.normal);
	if(diffuseFactor > 0.0f)
	{
		float specPower = max(surface.specular.a, 1.0f);
		float3 toEye = normalize(eyePos - surface.pos);
		float3 R = reflect(-lightVec, surface.normal);
		float specFactor = pow(max(dot(R, toEye), 0.0f), specPower);
		
		litColor += diffuseFactor * surface.diffuse * light.diffuse;
		litColor += specFactor * surface.specular  * light.specular;
	}

	return litColor / dot(light.att, float3(1.0f, d, d*d));
}

float3 spotLight( SurfaceInfo surface, Light light, float3 eyePos)
{
	float3 litColor = pointLight(surface, light, eyePos);
	
	float3 lightVec = normalize(light.pos - surface.pos);
	
	float s = pow(max(dot(-lightVec, light.dir), 0.0f), light.spotPow);

	return litColor * s;
}