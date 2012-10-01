
cbuffer constantBuffer
{
	float4x4 matFinal;
	float4x4 matWorld;
}

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
	float4 color = texDiffuse.Sample(ss, pIn.texcoord);

	clip(color.a-0.1);

	return color;
}