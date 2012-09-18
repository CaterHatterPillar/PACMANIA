#ifndef SHADERMANAGERDX_H
#define SHADERMANAGERDX_H

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3Dcompiler.h>

#include <Windows.h>
#include <WindowsX.h>

class ShaderManagerDX
{
private:
	ID3D11Device* device;
	ID3D11DeviceContext* devcon;

	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Buffer* cBufferPerFrame;

	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;

	ID3D10Blob* vs;
	ID3D10Blob* ps;
	ID3D10Blob* error;

	void createShaders();
	void createVertexShader();
	void createPixelShader();
	LPCSTR vertexShaderModel();
	LPCSTR pixelShaderModel();

	void createInputLayout();

public:
	ShaderManagerDX(ID3D11Device* device, ID3D11DeviceContext* devcon, D3D_FEATURE_LEVEL);
	~ShaderManagerDX();

	void initialize();
};

#endif