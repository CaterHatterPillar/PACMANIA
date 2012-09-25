#ifndef GRAPHICSCONTAINERDX_H
#define GRAPHICSCONTAINERDX_H

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include "../GraphicsContainer.h"

class GraphicsContainerDX : public GraphicsContainer
{
private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	ID3D11ShaderResourceView* texture;
	LPCTSTR textureFilename;
public:
	GraphicsContainerDX(LPCTSTR textureFilename,
						ShaderId vertexShaderId,
						ShaderId pixelShaderId,
						std::vector<PosNormTex>* vertices,
						std::vector<unsigned int>* indices,
						unsigned int numVertices, 
						unsigned int numIndices);
	virtual ~GraphicsContainerDX();

	void createVertexBuffer(ID3D11Device* device);
	void createIndexBuffer(ID3D11Device* device);
	void createTexture(ID3D11Device* device, LPCTSTR textureFilename);

	ID3D11Buffer* getVertexBuffer();
	ID3D11Buffer* getIndexBuffer();
	ID3D11ShaderResourceView* getTexture();

};

#endif //GRAPHICSCONTAINERDX_H