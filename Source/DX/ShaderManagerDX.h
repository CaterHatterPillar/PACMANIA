#ifndef SHADERMANAGERDX_H
#define SHADERMANAGERDX_H

#include <Windows.h>
#include <WindowsX.h>

#include <D3Dcompiler.h>

#include "ConstantBuffers.h"
#include "../Math/PacMath.h"

class ShaderManagerDX
{
private:
	ID3D11Device* device;
	ID3D11DeviceContext* devcon;

	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Buffer* cBufferPerFrame;
	ID3D11Buffer* cBufferLights;

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

	void createConstantBuffers();
	void createCBufferPerFrame();
	void createCBufferLights();
	int calcConstantBufferSize(int structSize);

public:
	ShaderManagerDX(ID3D11Device* device, ID3D11DeviceContext* devcon, D3D_FEATURE_LEVEL);
	~ShaderManagerDX();

	void initialize();

	void updateCBufferPerFrame(MatF4 final, MatF4 world, VecF3 cameraPosition);
	void updateCBufferLights(Light* lights, unsigned int numLights);

	ID3D11VertexShader* getVertexShader();
	ID3D11PixelShader* getPixelShader();
	ID3D11InputLayout* getInputLayout();
};

#endif