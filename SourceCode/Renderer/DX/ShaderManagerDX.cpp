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

	cBufferPerFrame->Release();

	vertexShader->Release();
	pixelShader->Release();
	inputLayout->Release();

	vs->Release();
	ps->Release();
}

void ShaderManagerDX::createShaders()
{
	createVertexShader();
	createPixelShader();
}

void ShaderManagerDX::createVertexShader()
{
	LPCSTR shaderModel = vertexShaderModel();
	D3DX11CompileFromFile("root/SourceCode/Renderer/DX/Shaders/Shader.hlsl", 0, 0, "VShader", shaderModel, 0, 0, 0, &vs, &error, 0);
	if(error != NULL)
	{
		MessageBox(NULL, "Vertex shader failed to compile", "Vertex shader error!", MB_OK | MB_ICONEXCLAMATION);
		error->Release();
	}

	device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), NULL, &vertexShader);
	devcon->VSSetShader(vertexShader, 0, 0);
}

void ShaderManagerDX::createPixelShader()
{
	LPCSTR shaderModel = pixelShaderModel();
	D3DX11CompileFromFile("root/SourceCode/Renderer/DX/Shaders/Shader.hlsl", 0, 0, "PShader", shaderModel, 0, 0, 0, &ps, &error, 0);
	if(error != NULL)
	{
		MessageBox(NULL, "Pixel shader failed to compile", "Pixel shader error!", MB_OK | MB_ICONEXCLAMATION);
		error->Release();
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

void ShaderManagerDX::createInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	/*D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};*/

	device->CreateInputLayout(ied, 3, vs->GetBufferPointer(), vs->GetBufferSize(), &inputLayout);
	devcon->IASetInputLayout(inputLayout);
}

void ShaderManagerDX::createConstantBuffers()
{
	createCBufferPerFrame();
}

void ShaderManagerDX::createCBufferPerFrame()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = calcConstantBufferSize(sizeof(CBufferPerFrame));
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	device->CreateBuffer(&bd, NULL, &cBufferPerFrame);
	devcon->VSSetConstantBuffers(0, 1, &cBufferPerFrame);
}

int ShaderManagerDX::calcConstantBufferSize(int structSize)
{
	return structSize + (16-(structSize%16));
}

void ShaderManagerDX::initialize()
{
	createShaders();
	createInputLayout();
	createConstantBuffers();
}

void ShaderManagerDX::updateCBufferPerFrame(D3DXMATRIX final, D3DXMATRIX world)
{
	CBufferPerFrame cBuffer;
	cBuffer.final = final;
	cBuffer.world = world;
	devcon->UpdateSubresource(cBufferPerFrame, 0, 0, &cBuffer, 0, 0);
}

ID3D11VertexShader* ShaderManagerDX::getVertexShader()
{
	return vertexShader;
}

ID3D11PixelShader* ShaderManagerDX::getPixelShader()
{
	return pixelShader;
}