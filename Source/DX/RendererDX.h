#ifndef RENDERERDX_H
#define RENDERERDX_H

#include "../Common.h"
#include "../Renderer.h"

#include "ShaderManagerDX.h"
#include "InputContainer.h"
#include "Cube.h"
#include "GraphicsContainerDX.h"
#include "TextureManagerDX.h"

#include "../GraphicsContainer.h"
#include "../Messaging/MsgLight.h"
#include "../Messaging/MsgDXWindowHandle.h"
#include "../Messaging/MsgCamera.h"
#include "../Messaging/SubscriptionMsg.h"
#include "../Messaging/ObserverDirector.h"
#include "../Singleton.h"

#include "../Math/PacMath.h"

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include <Windows.h>
#include <WindowsX.h>

class RendererDX : public Renderer
{
private:
	std::vector<GraphicsContainer*> renderQueue;
	std::vector<Light> lights;

	HWND hWnd;

	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* devcon;
	ID3D11RenderTargetView* backBuffer;
	ID3D11DepthStencilView* zBuffer;
	ID3D11RasterizerState* rasterizerState;
	ID3D11SamplerState* samplerStateDefault; 

	ShaderManagerDX* shaderManager;
	TextureManagerDX* textureManager;
	Cube* cube;

	MatF4 viewMatrix;
	MatF4 projectionMatrix;
	MatF4 viewProj;
	VecF3 cameraPosition;

	D3D_FEATURE_LEVEL featureLevel;
	char* featureLevelToString(D3D_FEATURE_LEVEL fl);

	void createDeviceAndSwapChain();
	void createDepthBuffer();
	void createBackBuffer();
	void createViewport();
	void createRasterizerState();
	void createSamplerState();
	void createShaderManager();
	void createTextureManager();

	void createCube();

	void handleMsgDXWindowHandle(Msg* msg);
	void handleMsgCamera(Msg* msg);
	void handleMsgRender(Msg* msg);
	void handleMsgLight(Msg* msg);

	void updateLighting();
	void renderContainer(GraphicsContainerDX* container, MatF4 translation, MatF4 rotation, MatF4 scaling);
protected:
public:
	RendererDX();
	~RendererDX();

	virtual void init()	;
	virtual void update(double delta);
	void renderFrame();
	void cleanUp();

	void input(InputContainer inputContainer);
};

#endif //RENDERERDX_H