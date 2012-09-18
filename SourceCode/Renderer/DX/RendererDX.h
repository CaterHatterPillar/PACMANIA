#ifndef RENDERERDX_H
#define RENDERERDX_H

#include "../../Common.h"
#include "../Renderer.h"

#include "ShaderManagerDX.h"

#include "../GraphicsContainer.h"
#include "../../Messaging/MsgDXWindowHandle.h"
#include "../../Messaging/SubscriptionMsg.h"
#include "../../Messaging/ObserverDirector.h"
#include "../../Singleton.h"

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include <Windows.h>
#include <WindowsX.h>

const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);

class RendererDX : public Renderer
{
private:
	std::vector<GraphicsContainer*> renderQueue;

	HWND hWnd;

	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* devcon;
	ID3D11RenderTargetView* backBuffer;
	ID3D11DepthStencilView* zBuffer;
	ID3D11RasterizerState* rasterizerState;

	ShaderManagerDX* shaderManager;

	D3D_FEATURE_LEVEL featureLevel;
	char* featureLevelToString(D3D_FEATURE_LEVEL fl);

	void createDeviceAndSwapChain();
	void createDepthBuffer();
	void createBackBuffer();
	void createViewport();
	void createRasterizerState();
	void createShaderManager();

	void handleMsgDXWindowHandle(Msg* msg);

protected:
public:
	RendererDX();
	~RendererDX();

	virtual void init()	;
	virtual void update(double delta);
	void renderFrame();
	void cleanUp();
};

#endif //RENDERERDX_H