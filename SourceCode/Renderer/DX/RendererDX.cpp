#include "RendererDX.h"

RendererDX::RendererDX()
{

}

RendererDX::~RendererDX()
{

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

	UINT numFeatureLevels = 6;

	D3D_FEATURE_LEVEL featureLevels[] = {	D3D_FEATURE_LEVEL_11_0,
											D3D_FEATURE_LEVEL_10_1,
											D3D_FEATURE_LEVEL_10_0,
											D3D_FEATURE_LEVEL_9_3,
											D3D_FEATURE_LEVEL_9_2,
											D3D_FEATURE_LEVEL_9_1};

	UINT numDriverTypes = 2;
	D3D_DRIVER_TYPE driverTypes[] = {D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_REFERENCE};

	int index = 0;
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
			
			//convert title to a unicode string
			
			LPCTSTR str = title;

			SetWindowText(hWnd, str);
			
			deviceCreated = true;
		}

		index++;
	}

}

void RendererDX::init()
{
	SubscriptionMsg* msg = new SubscriptionMsg(this, DX_WINDOW_HANDLE);
	Singleton<ObserverDirector>::get().push(msg);

	createDeviceAndSwapChain();
}

void RendererDX::update(double delta)
{
	Msg* msg = peek();
	while(msg != nullptr)
	{
		msg = pop();
		switch(msg->Type())
		{
			case DX_WINDOW_HANDLE:
				break;
		}
	}
}

void RendererDX::renderFrame()
{

}

void RendererDX::cleanUp()
{

}

void RendererDX::handleMsgDXWindowHandle(Msg* msg)
{
	MsgDXWindowHandle* msgDX = (MsgDXWindowHandle*)msg;

	hWnd = (*msgDX->getHandle());

	delete msgDX;
}