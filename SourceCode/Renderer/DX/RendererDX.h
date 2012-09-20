#ifndef RENDERERDX_H
#define RENDERERDX_H

#include "../../Common.h"
#include "../Renderer.h"

#include "ShaderManagerDX.h"
#include "Camera.h"
#include "InputContainer.h"
#include "Cube.h"

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
	Camera* camera;
	Cube* cube;


	D3D_FEATURE_LEVEL featureLevel;
	char* featureLevelToString(D3D_FEATURE_LEVEL fl);

	void createDeviceAndSwapChain();
	void createDepthBuffer();
	void createBackBuffer();
	void createViewport();
	void createRasterizerState();
	void createShaderManager();
	void createCamera();

	void createCube();

	void handleMsgDXWindowHandle(Msg* msg);

protected:
public:
	RendererDX();
	~RendererDX();

	virtual void init()	;
	virtual void update(double delta);
	void renderFrame();
	void cleanUp();

	void input(InputContainer input)
};

#endif //RENDERERDX_H