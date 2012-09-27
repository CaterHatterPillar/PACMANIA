
cbuffer constantBuffer
{
	float4x4 matFinal;
	float4x4 matWorld;
}

//Texture2D Texture;
//SamplerState ss
//{
//    Filter = MIN_MAG_MIP_LINEAR;
//    AddressU = Wrap;
//    AddressV = Wrap;
//};


struct VOut
{
    float4 position : SV_POSITION;
	float3 posW		: POSITION;
	float3 normalW	: NORMAL;
    float4 color	: COLOR;
};

VOut VShader(float3 position : POSITION, float3 normal : NORMAL, float4 color : COLOR)
{
    VOut output;
    output.position = mul(matFinal, float4(position, 1.0f));
	output.posW		= mul(matWorld, float4(position, 1.0f)).xyz;
	output.normalW	= mul(matWorld, float4(normal, 0.0f)).xyz;
    output.color	= color;

	//output.position = float4(position, 1.0);
	//output.posW = position;
	//output.normalW = normal;
	//output.color = color;
    
	
	return output;

}


float4 PShader(VOut pIn) : SV_TARGET
{
	return pIn.color;
}