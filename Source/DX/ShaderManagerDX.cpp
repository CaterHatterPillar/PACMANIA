#include "ShaderManagerDX.h"


ShaderManagerDX::ShaderManagerDX(ID3D11Device* device, ID3D11DeviceContext* devcon, D3D_FEATURE_LEVEL featureLevel)
{
	this->device		= device;
	this->devcon		= devcon;
	this->featureLevel	= featureLevel;
}

ShaderManagerDX::~ShaderManagerDX()
{
	/*
	A device reference seems to be removed somewhere that it shouldn't be.
	Not removing it here solves dx memory leaks.
	*/
	//device->Release(); 
	devcon->Release();

	cBufferPerFrame->Release();
	cBufferLights->Release();

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
	DWORD shaderCompileFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG)
	shaderCompileFlags |= D3DCOMPILE_DEBUG;
#endif

	LPCSTR shaderModel = vertexShaderModel();
	HRESULT hr = D3DX11CompileFromFile("../../Shaders/DX/Shader.hlsl", 0, 0, "VShader", shaderModel, shaderCompileFlags, 0, 0, &vs, &error, 0);
	if(FAILED(hr))
	{
		MessageBox(NULL, "Vertex shader failed to compile", "Vertex shader error!", MB_OK | MB_ICONEXCLAMATION);
		error->Release();
	}

	device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), NULL, &vertexShader);
	devcon->VSSetShader(vertexShader, 0, 0);
}

void ShaderManagerDX::createPixelShader()
{
		DWORD shaderCompileFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG)
	shaderCompileFlags |= D3DCOMPILE_DEBUG;
#endif

	LPCSTR shaderModel = pixelShaderModel();
	HRESULT hr = D3DX11CompileFromFile("../../Shaders/DX/Shader.hlsl", 0, 0, "PShader", shaderModel, shaderCompileFlags, 0, 0, &ps, &error, 0);
	if(FAILED(hr))
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
	/*D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};*/

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	device->CreateInputLayout(ied, 3, vs->GetBufferPointer(), vs->GetBufferSize(), &inputLayout);
	devcon->IASetInputLayout(inputLayout);
}

void ShaderManagerDX::createConstantBuffers()
{
	createCBufferPerFrame();
	createCBufferLights();
}

void ShaderManagerDX::createCBufferPerFrame()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage			= D3D11_USAGE_DEFAULT;
	bd.ByteWidth		= 128; //calcConstantBufferSize(sizeof(CBufferPerFrame));
	bd.BindFlags		= D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags	= 0;

	device->CreateBuffer(&bd, NULL, &cBufferPerFrame);
	devcon->VSSetConstantBuffers(0, 1, &cBufferPerFrame);
}

void ShaderManagerDX::createCBufferLights()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Usage			= D3D11_USAGE_DEFAULT;
	desc.ByteWidth		= calcConstantBufferSize(sizeof(CBufferLights));
	desc.BindFlags		= D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;

	HRESULT hr = device->CreateBuffer(&desc, NULL, &cBufferLights);
	if(FAILED(hr))
	{
		MessageBox(NULL, "CBufferLights creation failed!", "Constant Buffer error!", MB_OK | MB_ICONEXCLAMATION);
	}
	devcon->PSSetConstantBuffers(1, 1, &cBufferLights);
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

void ShaderManagerDX::updateCBufferPerFrame(MatF4 final, MatF4 world, VecF3 cameraPosition)
{
	CBufferPerFrame cBuffer;
	cBuffer.final			= final;
	cBuffer.world			= world;
	cBuffer.cameraPosition	= cameraPosition;
	devcon->UpdateSubresource(cBufferPerFrame, 0, 0, &cBuffer, 0, 0);
}

void ShaderManagerDX::updateCBufferLights(std::vector<Light> lights)
{
	CBufferLights cBuffer;
	if(lights.size() < MAX_NUM_LIGHTS)
		cBuffer.numLights = lights.size();
	else
		cBuffer.numLights = MAX_NUM_LIGHTS;

	for(unsigned int i=0; i<cBuffer.numLights; i++)
	{
		cBuffer.lights[i] = lights[i];
	}
	
	devcon->UpdateSubresource(cBufferLights, 0, 0, &cBuffer, 0, 0);
}

ID3D11VertexShader* ShaderManagerDX::getVertexShader()
{
	return vertexShader;
}

ID3D11PixelShader* ShaderManagerDX::getPixelShader()
{
	return pixelShader;
}

ID3D11InputLayout* ShaderManagerDX::getInputLayout()
{
	return inputLayout;
}