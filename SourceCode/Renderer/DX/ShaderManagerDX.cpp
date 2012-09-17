#include "ShaderManagerDX.h"


ShaderManagerDX::ShaderManagerDX(ID3D11Device* device, ID3D11DeviceContext* devcon, D3D_FEATURE_LEVEL featureLevel)
{
	this->device		= device;
	this->devcon		= devcon;
	this->featureLevel	= featureLevel;
}

ShaderManagerDX::~ShaderManagerDX()
{
	device->Release();
	devcon->Release();
}

void ShaderManagerDX::createShaders()
{
	createVertexShader();
	createVertexShader();
}

void ShaderManagerDX::createVertexShader()
{
	LPCSTR shaderModel = vertexShaderModel();
	D3DX11CompileFromFile("Files/Shaders/BasicShader.hlsl", 0, 0, "VShader", shaderModel, 0, 0, 0, &vs, &error, 0);
	if(error != NULL)
	{
		MessageBox(NULL, "Vertex shader failed to compile", "Vertex shader error!", MB_OK | MB_ICONEXCLAMATION);
	}

	device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), NULL, &vertexShader);
	devcon->VSSetShader(vertexShader, 0, 0);
}

void ShaderManagerDX::createPixelShader()
{
	LPCSTR shaderModel = pixelShaderModel();
	D3DX11CompileFromFile("Files/Shaders/BasicShader.hlsl", 0, 0, "PShader", shaderModel, 0, 0, 0, &ps, &error, 0);
	if(error != NULL)
	{
		MessageBox(NULL, "Pixel shader failed to compile", "Pixel shader error!", MB_OK | MB_ICONEXCLAMATION);
	}

	device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), NULL, &pixelShader);
	devcon->PSSetShader(pixelShader, 0, 0);
}

LPCSTR ShaderManagerDX::vertexShaderModel()
{
	if(featureLevel == D3D_FEATURE_LEVEL_11_0)
		return "vs_5_0";
	if(featureLevel == D3D_FEATURE_LEVEL_10_1)
		return "vs_4_1";
	if(featureLevel == D3D_FEATURE_LEVEL_10_0)
		return "vs_4_0";
	if(featureLevel == D3D_FEATURE_LEVEL_9_3)
		return "vs_4_0_level_9_3";
	if(featureLevel == D3D_FEATURE_LEVEL_9_2)
		return "vs_4_0_level_9_1";
	if(featureLevel == D3D_FEATURE_LEVEL_9_1)
		return "vs_4_0_level_9_1";

	return "Unknown";
}

LPCSTR ShaderManagerDX::pixelShaderModel()
{
	if(featureLevel == D3D_FEATURE_LEVEL_11_0)
		return "ps_5_0";
	if(featureLevel == D3D_FEATURE_LEVEL_10_1)
		return "ps_4_1";
	if(featureLevel == D3D_FEATURE_LEVEL_10_0)
		return "ps_4_0";
	if(featureLevel == D3D_FEATURE_LEVEL_9_3)
		return "ps_4_0_level_9_3";
	if(featureLevel == D3D_FEATURE_LEVEL_9_2)
		return "ps_4_0_level_9_1";
	if(featureLevel == D3D_FEATURE_LEVEL_9_1)
		return "ps_4_0_level_9_1";

	return "Unknown";
}

void ShaderManagerDX::initialize()
{
	createShaders();
}