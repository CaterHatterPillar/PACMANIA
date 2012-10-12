#ifndef TEXTUREMANAGERDX_H
#define TEXTUREMANAGERDX_H

#include "GraphicsContainerDX.h"

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include <Windows.h>
#include <WindowsX.h>

class TextureManagerDX
{
private:
	ID3D11ShaderResourceView* pacmanTexture;
	ID3D11ShaderResourceView* ghostTexture;
	ID3D11ShaderResourceView* pillTexture;
	ID3D11ShaderResourceView* bloodyPillTexture;

	LPCTSTR pacmanTextureFilename;
	LPCTSTR ghostTextureFilename;
	LPCTSTR pillTextureFilename;
	LPCTSTR bloodyPillTextureFilename;

public:
	TextureManagerDX();
	~TextureManagerDX();

	void init(ID3D11Device* device);
	ID3D11ShaderResourceView* getTexture(TextureId id);
};

#endif //TEXTUREMANAGERDX_H