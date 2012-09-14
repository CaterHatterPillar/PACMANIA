#ifndef RENDERERDX_H
#define RENDERERDX_H

#include "../../Common.h"
#include "../Renderer.h"
#include "../GraphicsContainer.h"

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include <Windows.h>
#include <WindowsX.h>

class RendererDX : public Renderer
{
private:
	std::vector<GraphicsContainer*> renderQueue;

	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* devcon;
	ID3D11RenderTargetView* backBuffer;
	ID3D11DepthStencilView* zBuffer;
	ID3D11RasterizerState* rasterizerState;

	D3D_FEATURE_LEVEL featureLevel;

	void createSwapChainAndDevice(HWND hWnd);

protected:
public:
	RendererDX();
	~RendererDX();

	void init()	;
	void update(double delta);
};

#endif //RENDERERDX_H