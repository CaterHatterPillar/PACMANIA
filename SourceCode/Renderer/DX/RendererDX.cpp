#include "RendererDX.h"

RendererDX::RendererDX()
{
	SubscriptionMsg* msg = new SubscriptionMsg(this, DX_WINDOW_HANDLE);
	Singleton<ObserverDirector>::get().push(msg);

	SubscriptionMsg* msg = new SubscriptionMsg(this, CAMERA);
	Singleton<ObserverDirector>::get().push(msg);
}

RendererDX::~RendererDX()
{
	cleanUp();
}

char* RendererDX::featureLevelToString(D3D_FEATURE_LEVEL fl)
{
	if(fl == D3D_FEATURE_LEVEL_11_0)
		return "11.0";
	if(fl == D3D_FEATURE_LEVEL_10_1)
		return "10.1";
	if(fl == D3D_FEATURE_LEVEL_10_0)
		return "10.0";
	if(fl == D3D_FEATURE_LEVEL_9_3)
		return "9.3";
	if(fl == D3D_FEATURE_LEVEL_9_2)
		return "9.2";
	if(fl == D3D_FEATURE_LEVEL_9_1)
		return "9.1";

	return "Unknown";

}

void RendererDX::createDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount			= 1;
	scd.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width	= SCREEN_WIDTH;
	scd.BufferDesc.Height	= SCREEN_HEIGHT;
	scd.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow		= hWnd;
	scd.SampleDesc.Count	= 4;
	scd.Windowed			= true;
	scd.Flags				= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	UINT numFeatureLevels = 4;

	D3D_FEATURE_LEVEL featureLevels[] = {	D3D_FEATURE_LEVEL_11_0,
											D3D_FEATURE_LEVEL_10_1,
											D3D_FEATURE_LEVEL_10_0,
											D3D_FEATURE_LEVEL_9_3 };

	UINT numDriverTypes = 2;
	D3D_DRIVER_TYPE driverTypes[] = {D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_REFERENCE};

	unsigned int index = 0;
	bool deviceCreated = false;

	while(index < numDriverTypes && !deviceCreated)
	{	
		HRESULT hr;
		D3D_DRIVER_TYPE driverType = driverTypes[index];
		hr = D3D11CreateDeviceAndSwapChain(	NULL,
											driverType, //D3D_DRIVER_TYPE_HARDWARE,
											NULL,
											NULL, //D3D11_CREATE_DEVICE_DEBUG,	//Enables shader debugging with PIX
											featureLevels,
											numFeatureLevels,
											D3D11_SDK_VERSION, 
											&scd,
											&swapChain,
											&device,
											&featureLevel,
											&devcon);

		if(SUCCEEDED(hr))
		{
			char title[256];
			sprintf_s(	title,
						sizeof(title),
						"Wonderland | Direct3D 11.0 device initiated with Direct3D %s feature level",
						featureLevelToString(featureLevel));
			SetWindowText(hWnd, title);
			
			deviceCreated = true;
		}

		index++;
	}
}

void RendererDX::createDepthBuffer()
{
	D3D11_TEXTURE2D_DESC texd;
	ZeroMemory(&texd, sizeof(texd));

	texd.Width = SCREEN_WIDTH;
	texd.Height = SCREEN_HEIGHT;
	texd.ArraySize = 1;
	texd.MipLevels = 1;
	texd.SampleDesc.Count = 4;
	texd.Format = DXGI_FORMAT_D32_FLOAT;
	texd.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ID3D11Texture2D* depthBuffer;
	device->CreateTexture2D(&texd, NULL, &depthBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	device->CreateDepthStencilView(depthBuffer, &dsvd, &zBuffer);
	if(featureLevel != D3D_FEATURE_LEVEL_9_3)
		depthBuffer->Release();
}

void RendererDX::createBackBuffer()
{
	ID3D11Texture2D* texBackBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&texBackBuffer);

	device->CreateRenderTargetView(texBackBuffer, NULL, &backBuffer);
	texBackBuffer->Release();

	devcon->OMSetRenderTargets(1, &backBuffer, zBuffer);
}

void RendererDX::createViewport()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX	= 0;
	viewport.TopLeftY	= 0;
	viewport.Width		= SCREEN_WIDTH;
	viewport.Height		= SCREEN_HEIGHT;
	viewport.MinDepth	= 0;
	viewport.MaxDepth	= 1;

	devcon->RSSetViewports(1, &viewport);
}

void RendererDX::createRasterizerState()
{
	D3D11_RASTERIZER_DESC rsd;

	rsd.CullMode				= D3D11_CULL_BACK;
	rsd.FillMode				= D3D11_FILL_SOLID;
	rsd.FrontCounterClockwise	= false;
	rsd.DepthBias				= false;
	rsd.DepthBiasClamp			= 0;
	rsd.SlopeScaledDepthBias	= 0;
	rsd.DepthClipEnable			= true;
	rsd.ScissorEnable			= false;
	rsd.MultisampleEnable		= false;
	rsd.AntialiasedLineEnable	= true;

	device->CreateRasterizerState(&rsd, &rasterizerState);
	devcon->RSSetState(rasterizerState);
}

void RendererDX::createShaderManager()
{
	shaderManager = new ShaderManagerDX(device, devcon, featureLevel);
	shaderManager->initialize();
}

void RendererDX::createCamera()
{
	camera = new Camera();
	camera->setLens(PI/4, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 1.0f, 100.0f);
}

void RendererDX::createCube()
{
	cube = new Cube(device);
	cube->initialize();
}

void RendererDX::init()
{
	createDeviceAndSwapChain();
	createDepthBuffer();
	createBackBuffer();
	createViewport();
	createRasterizerState();

	createShaderManager();
	createCamera();
	createCube();
}

void RendererDX::update(double delta)
{
	Msg* msg = peek();
	while(msg != nullptr)
	{
		switch(msg->Type())
		{
			case DX_WINDOW_HANDLE:
				handleMsgDXWindowHandle(msg);
				break;
			case CAMERA:
				break;
		}

		msg = pop();
	}
}

void RendererDX::renderFrame()
{
	camera->rebuildView();

	D3DXMATRIX viewProj = camera->getView() * camera->getProjection();
	D3DXMATRIX final = cube->getWorldMatrix() * viewProj;
	shaderManager->updateCBufferPerFrame(final, cube->getWorldMatrix());

	devcon->ClearRenderTargetView(backBuffer, BLACK);
	devcon->ClearDepthStencilView(zBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);

	devcon->VSSetShader(shaderManager->getVertexShader(), 0, 0);
	devcon->PSSetShader(shaderManager->getPixelShader(), 0, 0);
	devcon->IASetInputLayout(shaderManager->getInputLayout());

	UINT stride = sizeof(Vertex); 
	UINT offset = 0;

	devcon->OMSetDepthStencilState(0, 0);

	ID3D11Buffer* vertexBuffer = cube->getVertexBuffer();

	devcon->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	devcon->IASetIndexBuffer(cube->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devcon->DrawIndexed(cube->getNumIndices(), 0, 0);

	swapChain->Present(0, 0);
}

void RendererDX::cleanUp()
{
	device->Release();
	devcon->Release();
	zBuffer->Release();
	backBuffer->Release();

	delete shaderManager;
}

void RendererDX::handleMsgDXWindowHandle(Msg* msg)
{
	MsgDXWindowHandle* msgDX = (MsgDXWindowHandle*)msg;

	hWnd = (*msgDX->getHandle());

	delete msgDX;
}

void RendererDX::handleMsgCamera(Msg* msg)
{
	MsgCamera msgCamera = (MsgCamera*)msg;
	viewMatrix = msgCamera.View();
	projectionMatrix = msgCamera.Proj();
}

void RendererDX::input(InputContainer inputContainer)
{
	float velocityModifier = 0.1f; 
	float velocity = 40.0f * velocityModifier;

	if(inputContainer.keys[VK_W])
		camera->walk(velocity);
	if(inputContainer.keys[VK_S])
		camera->walk(-velocity);
	if(inputContainer.keys[VK_D])
		camera->strafe(velocity);
	if(inputContainer.keys[VK_A])
		camera->strafe(-velocity);
	if(inputContainer.keys[VK_Z])
		camera->verticalWalk(velocity);
	if(inputContainer.keys[VK_X])
		camera->verticalWalk(-velocity);

	if(inputContainer.keys[VK_1])
		velocityModifier = 1;
	if(inputContainer.keys[VK_2])
		velocityModifier = 2;
	if(inputContainer.keys[VK_3])
		velocityModifier = 3;
	if(inputContainer.keys[VK_4])
		velocityModifier = 4;

	float angleX = (inputContainer.mouseDeltaX) * 0.001f;
	float angleY = (inputContainer.mouseDeltaY) * 0.001f;

	camera->rotateY(angleX);
	camera->pitch(angleY);
}