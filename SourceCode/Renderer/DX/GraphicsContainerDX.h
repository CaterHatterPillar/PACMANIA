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
public:
	GraphicsContainerDX(ShaderId vertexShaderId,
						ShaderId pixelShaderId,
						TextureId textureId,
						std::vector<PosNormTex>* vertices,
						std::vector<unsigned int>* indices,
						unsigned int numVertices, 
						unsigned int numIndices,
						unsigned int numFaces,
						unsigned int stride,
						unsigned int offset);
	virtual ~GraphicsContainerDX();

	void createVertexBuffer(ID3D11Device* device);
	void createIndexBuffer(ID3D11Device* device);

	void setTexture(ID3D11ShaderResourceView* texture);

	ID3D11Buffer* getVertexBuffer();
	ID3D11Buffer* getIndexBuffer();
	ID3D11ShaderResourceView* getTexture();
};

#endif //GRAPHICSCONTAINERDX_H