
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