#include "TextureManagerDX.h"

TextureManagerDX::TextureManagerDX()
{
	pacmanTexture		= NULL;
	ghostTexture		= NULL;
	pillTexture			= NULL;
	bloodyPillTexture	= NULL;

	pacmanTextureFilename		= "root/Textures/PacmanTex.png";
	ghostTextureFilename		= "root/Textures/PlaceHolder.png";
	pillTextureFilename			= "root/Textures/Pill.png";
	bloodyPillTextureFilename	= "root/Textures/BloodyPill.png";
}

TextureManagerDX::~TextureManagerDX()
{
	if(pacmanTexture)
		pacmanTexture->Release();
	if(ghostTexture)
		ghostTexture->Release();
	if(pillTexture)
		pillTexture->Release();
	if(bloodyPillTexture)
		bloodyPillTexture->Release();
}

void TextureManagerDX::init(ID3D11Device* device)
{	
	HRESULT hr;
	D3DX11CreateShaderResourceViewFromFile(device, pacmanTextureFilename, NULL, NULL, &pacmanTexture, &hr);
	if(FAILED(hr))
		MessageBox(NULL, "Failed to create pacmanTexture", "TextureManagerDX error!", MB_OK | MB_ICONEXCLAMATION);

	D3DX11CreateShaderResourceViewFromFile(device, ghostTextureFilename, NULL, NULL, &ghostTexture, &hr);
	if(FAILED(hr))
		MessageBox(NULL, "Failed to create ghostTexture", "TextureManagerDX error!", MB_OK | MB_ICONEXCLAMATION);

	D3DX11CreateShaderResourceViewFromFile(device, pillTextureFilename, NULL, NULL, &pillTexture, &hr);
	if(FAILED(hr))
		MessageBox(NULL, "Failed to create pillTexture", "TextureManagerDX error!", MB_OK | MB_ICONEXCLAMATION);

	D3DX11CreateShaderResourceViewFromFile(device, bloodyPillTextureFilename, NULL, NULL, &bloodyPillTexture, &hr);
	if(FAILED(hr))
		MessageBox(NULL, "Failed to create bloodyPillTexture", "TextureManagerDX error!", MB_OK | MB_ICONEXCLAMATION);
}

ID3D11ShaderResourceView* TextureManagerDX::getTexture(TextureId id)
{
	ID3D11ShaderResourceView* texture = NULL;

	switch(id)
	{
	case TEXTURE_PACMAN:
		texture = pacmanTexture;
		break;
	case TEXTURE_GHOST:
		texture = ghostTexture;
		break;
	case TEXTURE_PILL:
		texture = pillTexture;
		break;
	case TEXTURE_PILL_BLOODY:
		texture = bloodyPillTexture;
		break;
	default:
		texture = NULL;
		break;
	}

	return texture;
}