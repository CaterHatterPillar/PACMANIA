
#include "Light.hlsl"

cbuffer constantBuffer : register(b0)
{
	float4x4 matFinal;
	float4x4 matWorld;
	float3 cameraPosition;
};

cbuffer cbLights : register(b1)
{
	Light lights[10];
	uint numLights;
};

Texture2D texDiffuse : register( t0 );
SamplerState ss : register( s0 );


struct VOut
{
    float4 position : SV_POSITION;
	float3 posW		: POSITION;
	float3 normalW	: NORMAL;
    float2 texcoord	: TEXCOORD;
};

VOut VShader(float3 position : POSITION, float3 normal : NORMAL, float2 texcoord : TEXCOORD)
{
    VOut output;
    output.position = mul(matFinal, float4(position, 1.0f));
	output.posW		= mul(matWorld, float4(position, 1.0f)).xyz;
	output.normalW	= mul(matWorld, float4(normal, 0.0f)).xyz;
    output.texcoord	= texcoord;

	//output.position = float4(position, 1.0);
	//output.posW = position;
	//output.normalW = normal;
	//output.texcoord = texcoord;
    
	
	return output;

}


float4 PShader(VOut pIn) : SV_TARGET
{
	float4 color 		= texDiffuse.Sample(ss, pIn.texcoord);
	float4 ambient 	= float4(0.1f, 0.1f, 0.1f, 1.0f); 
	float4 diffuse 	= float4(1.0f, 1.0f, 1.0f, 1.0f);
	float4 specular 	= float4(1.0f, 1.0f, 1.0f, 0.0f);
	specular.a *= 256.0f;
	
	float3 normalW = normalize(pIn.normalW);
	
	SurfaceInfo surface = {pIn.posW, normalW, diffuse, specular};
	
	float3 litColor = float3(0.0f, 0.0f, 0.0f);
	for(int i=0; i<numLights; i++)
		litColor += spotLight(surface, lights[i], cameraPosition);
	
	litColor += ambient;
	
	//clip(color.a-0.1);
	//color = color * lights[0].ambient;
	
	return color * float4(litColor, 1.0f);
}